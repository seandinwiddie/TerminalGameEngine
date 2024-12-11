import { Level } from '../../engine/level.js';
import { AudioManager } from '../../engine/audioManager.js';
import { Simulation } from '../../engine/simulation.js';
import { EventEmitter } from 'events';

export class PongLevel extends Level {
  constructor() {
    super();
    this.leftPaddle = null;
    this.rightPaddle = null;
    this.ball = null;
    this.events = new EventEmitter();
    this.leftScore = 0;
    this.rightScore = 0;
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

    // Create paddles
    this.leftPaddle = this.createPaddle(5, 10, 'w', 's');
    this.rightPaddle = this.createPaddle(this.getWorldSizeX() - 6, 10, 'i', 'k');
    
    simulation.tryAddEntity(this.leftPaddle);
    simulation.tryAddEntity(this.rightPaddle);

    // Create ball
    this.ball = this.createBall(
      this.getWorldSizeX() / 2,
      this.getWorldSizeY() / 2
    );
    
    this.ball.events.on('leftScore', () => {
      this.rightScore++;
      this.checkWinCondition();
      AudioManager.getInstance().playFx('Resources/Sounds/Pong/Score.wav');
    });

    this.ball.events.on('rightScore', () => {
      this.leftScore++;
      this.checkWinCondition();
      AudioManager.getInstance().playFx('Resources/Sounds/Pong/Score.wav');
    });

    simulation.tryAddEntity(this.ball);

    // Create score display
    this.initScoreDisplay();

    AudioManager.getInstance().playMusic('Resources/Music/Pong.wav');
  }

  checkWinCondition() {
    if (this.leftScore >= 5 || this.rightScore >= 5) {
      this.onGameOver();
    } else {
      this.resetBall();
    }
  }

  resetBall() {
    this.ball.setPosition(
      this.getWorldSizeX() / 2,
      this.getWorldSizeY() / 2
    );
    this.ball.randomizeDirection();
  }

  initScoreDisplay() {
    const simulation = Simulation.getInstance();
    const printer = simulation.getUIPrinter();
    
    const leftScoreX = Math.floor(this.getWorldSizeX() * 0.25);
    const rightScoreX = Math.floor(this.getWorldSizeX() * 0.75);
    const scoreY = 2;

    printer.printOnHeader(`${this.leftScore}`, leftScoreX, 'white');
    printer.printOnHeader(`${this.rightScore}`, rightScoreX, 'white');
  }

  onGameOver() {
    if (this.isGameOver()) return;

    super.onGameOver();
    AudioManager.getInstance().stopMusic();
    AudioManager.getInstance().playFx('Resources/Sounds/Pong/GameOver.wav');
  }

  getShowGameOverScreenDelay() {
    return 0.5;
  }

  getPersistenceFilePath() {
    return 'Resources/Persistence/Pong.txt';
  }

  getGameOverWindowPath() {
    return 'Resources/GameOverWindows/Pong.txt';
  }
} 