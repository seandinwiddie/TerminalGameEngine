import { Level } from '../../engine/level.js';
import { AudioManager } from '../../engine/audioManager.js';
import { Simulation } from '../../engine/simulation.js';
import { EventEmitter } from 'events';

export class EndlessRunnerLevel extends Level {
  constructor() {
    super();
    this.bunny = null;
    this.obstacleSpawner = null;
    this.events = new EventEmitter();
    this.score = 0;
  }

  getWorldSizeX() {
    return 100;
  }

  getWorldSizeY() {
    return 30;
  }

  getScreenPadding() {
    return 4;
  }

  loadInSimulation() {
    super.loadInSimulation();
    const simulation = Simulation.getInstance();

    // Bunny setup
    const bunnyStartingY = simulation.getScreenPadding();
    this.bunny = this.createBunny(9, bunnyStartingY);
    this.bunny.events.on('obstacleHit', () => this.onGameOver());
    simulation.tryAddEntity(this.bunny);

    // Obstacles spawner setup
    const spawnerPosX = this.getWorldSizeX() - this.getScreenPadding();
    
    const spawnConfig = {
      minSpawnDelays: [0.9, 0.4, 0.28, 0.25, 0.22, 0.22],
      maxSpawnDelays: [1, 0.6, 0.43, 0.4, 0.32, 0.22],
      moveSpeeds: [-8, -16, -32, -40, -48, -48],
      ySpawnPoints: [4, 8, 12],
      increaseIntensityEverySeconds: 10,
      stopSpawningWhenPhaseChangesDuration: 1
    };

    this.obstacleSpawner = this.createObstacleSpawner(spawnerPosX, spawnConfig);
    simulation.tryAddEntity(this.obstacleSpawner);

    AudioManager.getInstance().playMusic('Resources/Music/EndlessRunner.wav');
  }

  onGameOver() {
    if (this.isGameOver()) return;

    super.onGameOver();
    AudioManager.getInstance().stopMusic();
    AudioManager.getInstance().playFx('Resources/Sounds/EndlessRunner/GameOver.wav');
  }

  async onPostGameOverDelayEnded() {
    super.onPostGameOverDelayEnded();
    const savedBestScore = await this.loadBestScore();
    
    if (this.score > savedBestScore) {
      await this.saveBestScore(this.score);
    }

    this.showGameOverScreen(this.score, savedBestScore);
  }

  getShowGameOverScreenDelay() {
    return 0.5;
  }

  getPersistenceFilePath() {
    return 'Resources/Persistence/EndlessRunner.txt';
  }

  getGameOverWindowPath() {
    return 'Resources/GameOverWindows/EndlessRunner.txt';
  }
} 