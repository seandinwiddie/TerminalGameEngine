import { Level } from '../../engine/level.js';
import { AudioManager } from '../../engine/audioManager.js';
import { Simulation } from '../../engine/simulation.js';
import { EventEmitter } from 'events';
import { Terminal } from '../../engine/terminal.js';

export class SpaceInvadersLevel extends Level {
  constructor() {
    super();
    this.waveNumber = 1;
    this.score = 0;
    this.isLoadingWave = false;
    this.startedLoadingWaveTime = 0;
    this.aliensController = null;
    this.events = new EventEmitter();
  }

  loadAliens() {
    console.log('Loading aliens for wave:', this.waveNumber);
    // Create a grid of aliens (5x11 is traditional for Space Invaders)
    const rows = 5;
    const cols = 11;
    const startX = 10;
    const startY = 5;
    const spacingX = 4;
    const spacingY = 2;

    for (let row = 0; row < rows; row++) {
      for (let col = 0; col < cols; col++) {
        const x = startX + (col * spacingX);
        const y = startY + (row * spacingY);
        const alien = this.createAlien(x, y, row);
        Simulation.getInstance().tryAddEntity(alien);
      }
    }
  }

  loadPlayerTank() {
    console.log('Loading player tank');
    const tank = this.createPlayerTank(
      this.getWorldSizeX() / 2,
      this.getWorldSizeY() - 3
    );
    Simulation.getInstance().tryAddEntity(tank);
  }

  loadShields() {
    console.log('Loading shields');
    const shieldPositions = [20, 40, 60, 80];
    shieldPositions.forEach(x => {
      const shield = this.createShield(x, this.getWorldSizeY() - 8);
      Simulation.getInstance().tryAddEntity(shield);
    });
  }

  createAlien(x, y, type) {
    // Placeholder for alien creation
    return {
      position: { x, y },
      type: type,
      render: () => 'M'
    };
  }

  createPlayerTank(x, y) {
    const tank = {
      position: { x, y },
      speed: 2,
      render: () => 'W',
      update: function() {
        const terminal = Terminal.getInstance();
        
        // Handle movement
        if (terminal.pressedKeys.has('left') && this.position.x > 1) {
          this.position.x -= this.speed;
        }
        if (terminal.pressedKeys.has('right') && this.position.x < 100 - 2) {
          this.position.x += this.speed;
        }

        // Handle shooting
        if (terminal.pressedKeys.has('space')) {
          this.shoot();
        }
      },
      shoot: function() {
        const bullet = {
          position: { x: this.position.x, y: this.position.y - 1 },
          render: () => '|',
          update: function() {
            this.position.y--;
            if (this.position.y < 0) {
              Simulation.getInstance().entities.delete(this);
            }
          }
        };
        Simulation.getInstance().tryAddEntity(bullet);
        AudioManager.getInstance().playFx('Resources/Sounds/SpaceInvaders/Shoot.wav');
      }
    };
    return tank;
  }

  createShield(x, y) {
    // Placeholder for shield creation
    return {
      position: { x, y },
      render: () => '#'
    };
  }

  initHeader() {
    const simulation = Simulation.getInstance();
    const printer = simulation.getUIPrinter();
    printer.printOnHeader(`Score: ${this.score}`, 2, 'white');
    printer.printOnHeader(`Wave: ${this.waveNumber}`, this.getWorldSizeX() - 10, 'white');
  }

  getWorldSizeX() {
    return 100;
  }

  getWorldSizeY() {
    return 50;
  }

  getScreenPadding() {
    return 6;
  }

  loadInSimulation() {
    super.loadInSimulation();
    const simulation = Simulation.getInstance();

    this.loadAliens();
    this.loadPlayerTank();
    this.loadShields();
    this.initHeader();

    AudioManager.getInstance().playMusic('Resources/Music/SpaceInvaders.wav');
  }

  update() {
    super.update();
    this.loadNewWave();
  }

  onGameOver() {
    if (this.isGameOver()) return;

    super.onGameOver();
    AudioManager.getInstance().stopMusic();
    AudioManager.getInstance().playFx('Resources/Sounds/SpaceInvaders/GameOver.wav');
  }

  async onPostGameOverDelayEnded() {
    super.onPostGameOverDelayEnded();
    const savedBestScore = await this.loadBestScore();
    
    if (this.score > savedBestScore) {
      await this.saveBestScore(this.score);
    }

    this.showGameOverScreen(this.score, savedBestScore);
    AudioManager.getInstance().playFx('Resources/Sounds/SpaceInvaders/ShowEndScreen.wav');
  }

  showGameOverScreen(score, bestScore) {
    const message = score > bestScore 
      ? `new record: ${score}!` 
      : `score: ${score}, best: ${bestScore}`;

    const leftSpacing = ' '.repeat(Math.floor((42 - message.length) / 2));
    const centeredMessage = leftSpacing + message;

    this.gameOverWindow.writeString(centeredMessage, '$');
    
    Simulation.getInstance()
      .getUIPrinter()
      .printWindow(this.gameOverWindow, 'white', 'centerX_topY');
  }

  increasePlayerScore(increment) {
    this.score += increment;
    this.printScore();
  }

  isLoadingWave() {
    return this.isLoadingWave;
  }

  getShowGameOverScreenDelay() {
    return 0.2;
  }

  getPersistenceFilePath() {
    return 'Resources/Persistence/SpaceInvaders.txt';
  }

  getGameOverWindowPath() {
    return 'Resources/GameOverWindows/SpaceInvaders.txt';
  }
} 