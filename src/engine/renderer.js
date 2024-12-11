const blessed = require('blessed');

class TerminalRenderer {
  constructor() {
    this.screen = blessed.screen({
      smartCSR: true,
      title: 'Terminal Game Engine'
    });
    
    this.gameArea = blessed.box({
      parent: this.screen,
      top: 0,
      left: 0,
      width: '100%',
      height: '100%'
    });
  }

  render(gameObjects) {
    // Clear previous frame
    this.gameArea.setContent('');
    
    // Render each game object
    for (const obj of gameObjects) {
      this.renderGameObject(obj);
    }
    
    this.screen.render();
  }
} 