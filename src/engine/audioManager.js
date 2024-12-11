import playSound from 'play-sound';
import { EventEmitter } from 'events';

export class AudioManager {
  static #instance = null;
  
  constructor() {
    if (AudioManager.#instance) {
      return AudioManager.#instance;
    }
    
    this.player = playSound();
    this.currentMusic = null;
    this.events = new EventEmitter();
    this.isMuted = false;
    
    AudioManager.#instance = this;
  }

  static getInstance() {
    if (!AudioManager.#instance) {
      AudioManager.#instance = new AudioManager();
    }
    return AudioManager.#instance;
  }

  playMusic(filePath, volume = 1.0) {
    if (this.isMuted) return;
    
    this.stopMusic();
    this.currentMusic = this.player.play(filePath, { volume }, (err) => {
      if (err) console.error(`Error playing music: ${err}`);
    });
  }

  stopMusic() {
    if (this.currentMusic) {
      this.currentMusic.kill();
      this.currentMusic = null;
    }
  }

  playFx(filePath, volume = 1.0) {
    if (this.isMuted) return;

    this.player.play(filePath, { volume }, (err) => {
      if (err) console.error(`Error playing sound effect: ${err}`);
    });
  }

  toggleMute() {
    this.isMuted = !this.isMuted;
    if (this.isMuted) {
      this.stopMusic();
    }
    this.events.emit('muteChanged', this.isMuted);
  }

  isMuted() {
    return this.isMuted;
  }
}