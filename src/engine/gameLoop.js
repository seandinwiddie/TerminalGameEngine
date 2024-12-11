import blessed from 'blessed';
import { Terminal } from './terminal.js';
import { AudioManager } from './audioManager.js';
import { Simulation } from './simulation.js';
import { SpaceInvadersLevel } from '../games/spaceInvaders/spaceInvadersLevel.js';
import { EndlessRunnerLevel } from '../games/platformer/endlessRunnerLevel.js';
import { PuzzleLevel } from '../games/platformer/puzzleLevel.js';
import { PongLevel } from '../games/pong/pongLevel.js';

export class GameLoop {
  constructor() {
    this.terminal = Terminal.getInstance();
    this.audioManager = AudioManager.getInstance();
    this.simulation = Simulation.getInstance();
  }

  async showLevelSelection() {
    console.log('Showing level selection menu');
    const screen = this.terminal.getScreen();
    this.terminal.clear();

    const menu = blessed.box({
      parent: screen,
      top: 'center',
      left: 'center',
      width: '50%',
      height: '70%',
      content: `
        Terminal Game Engine
        
        1. Space Invaders
        2. Endless Runner
        3. Puzzle Platform
        4. Pong
        
        Controls:
        Space Invaders:
        left/right: move, space: shoot
        
        Endless Runner:
        space: jump
        
        Puzzle Platform:
        left/right: move, space: jump
        
        Pong:
        a/d: Player 1 move
        left/right arrow: Player 2 move
        
        --------------------------- Credits:
        Music by 'Cody O'Quinn'
        
        Press 1-4 to select a game...`,
      border: {
        type: 'line'
      },
      style: {
        border: {
          fg: 'white'
        }
      },
      keys: true,
      input: true
    });

    screen.render();

    return new Promise((resolve) => {
      console.log('Waiting for key input...');
      menu.key(['1', '2', '3', '4'], (ch, key) => {
        console.log('Menu key pressed:', { ch, key });
        const selection = key.name || ch;
        console.log('Selection:', selection);
        
        switch(selection) {
          case '1': 
            console.log('Starting Space Invaders');
            resolve(new SpaceInvadersLevel()); 
            break;
          case '2': 
            console.log('Starting Endless Runner');
            resolve(new EndlessRunnerLevel()); 
            break;
          case '3': 
            console.log('Starting Puzzle Level');
            resolve(new PuzzleLevel()); 
            break;
          case '4': 
            console.log('Starting Pong');
            resolve(new PongLevel()); 
            break;
        }
      });

      // Make sure the menu can receive input
      menu.focus();
    });
  }

  async start() {
    console.log('Game loop starting');
    while (true) {
      this.audioManager.stopMusic();
      const level = await this.showLevelSelection();
      console.log('Level selected:', level?.constructor.name);
      
      if (level) {
        while (true) {
          const returnToMainMenu = await this.loopSimulation(level);
          if (returnToMainMenu) {
            console.log('Returning to main menu');
            break;
          }
        }
      }
    }
  }

  async loopSimulation(level) {
    console.log('Starting game simulation');
    this.simulation.loadLevel(level);
    
    // Game loop
    while (!level.isTerminated()) {
      // Process input and update game state
      this.simulation.step();
      
      // Check for escape key to return to menu
      if (await this.terminal.isKeyPressed('escape')) {
        console.log('Escape pressed, returning to menu');
        return true;
      }

      // Add a small delay to prevent CPU overload
      await new Promise(resolve => setTimeout(resolve, 50));
    }
    
    return false;
  }
} 