import { Level } from '../../engine/level.js';
import { AudioManager } from '../../engine/audioManager.js';
import { Simulation } from '../../engine/simulation.js';
import { StaticCollider } from '../../engine/staticCollider.js';
import { EventEmitter } from 'events';

export class PuzzleLevel extends Level {
  constructor() {
    super();
    this.bunny = null;
    this.flag = null;
    this.events = new EventEmitter();
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
    this.bunny = this.createBunny(5, 8);
    simulation.tryAddEntity(this.bunny);

    // Left platform
    const platform = new StaticCollider(24, 11, 12, 1, '#');
    simulation.tryAddEntity(platform);

    // Right flag platform
    const flagPlatform = new StaticCollider(63, 15, 16, 1, '#');
    simulation.tryAddEntity(flagPlatform);

    // Flag
    this.flag = this.createFlag(70, 16);
    this.flag.events.on('touchBunny', () => this.onGameOver());
    simulation.tryAddEntity(this.flag);

    // Add pressure plates and doors
    this.setupPuzzleElements();

    AudioManager.getInstance().playMusic('Resources/Music/Puzzle.wav');
  }

  setupPuzzleElements() {
    const simulation = Simulation.getInstance();

    // Add pressure plates
    const plate1 = this.createPressurePlate(28, 10);
    const plate2 = this.createPressurePlate(45, 10);
    
    // Add automatic doors
    const door1 = this.createAutomaticDoor(35, 12);
    const door2 = this.createAutomaticDoor(55, 12);

    // Link plates to doors
    plate1.events.on('pressed', () => door1.open());
    plate1.events.on('released', () => door1.close());
    
    plate2.events.on('pressed', () => door2.open());
    plate2.events.on('released', () => door2.close());

    simulation.tryAddEntity(plate1);
    simulation.tryAddEntity(plate2);
    simulation.tryAddEntity(door1);
    simulation.tryAddEntity(door2);
  }

  onGameOver() {
    if (this.isGameOver()) return;

    super.onGameOver();
    AudioManager.getInstance().stopMusic();
    AudioManager.getInstance().playFx('Resources/Sounds/Platform/LevelComplete.wav');
  }

  getShowGameOverScreenDelay() {
    return 0.5;
  }

  getPersistenceFilePath() {
    return 'Resources/Persistence/Puzzle.txt';
  }

  getGameOverWindowPath() {
    return 'Resources/GameOverWindows/Puzzle.txt';
  }
} 