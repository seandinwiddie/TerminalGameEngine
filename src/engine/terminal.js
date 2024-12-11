import blessed from 'blessed';

export class Terminal {
  static #instance = null;

  constructor() {
    if (Terminal.#instance) {
      return Terminal.#instance;
    }

    this.screen = blessed.screen({
      smartCSR: true,
      title: 'Terminal Game Engine',
      useBCE: true,
      fullUnicode: true
    });

    this.gameBox = blessed.box({
      parent: this.screen,
      top: 0,
      left: 0,
      width: '100%',
      height: '100%',
      style: {
        fg: 'white'
      }
    });

    this.colors = {
      WHITE: 'white',
      RED: 'red',
      GREEN: 'green',
      BLUE: 'blue',
      CYAN: 'cyan',
      MAGENTA: 'magenta',
      YELLOW: 'yellow',
      GREY: 'grey'
    };

    this.pressedKeys = new Set();
    this.setupKeyHandling();
    
    Terminal.#instance = this;
  }

  static getInstance() {
    if (!Terminal.#instance) {
      Terminal.#instance = new Terminal();
    }
    return Terminal.#instance;
  }

  setupKeyHandling() {
    console.log('Setting up key handling');
    
    // Map key names to standardized values
    this.keyMap = {
      left: ['left', 'a', 'h'],
      right: ['right', 'd', 'l'],
      space: ['space', ' '],
      escape: ['escape', 'q']
    };

    this.screen.on('keypress', (ch, key) => {
      console.log('Terminal key pressed:', { ch, key });
      
      // Handle raw character input
      if (ch) {
        for (const [action, keys] of Object.entries(this.keyMap)) {
          if (keys.includes(ch)) {
            this.pressedKeys.add(action);
          }
        }
      }
      
      // Handle special keys
      if (key && key.name) {
        for (const [action, keys] of Object.entries(this.keyMap)) {
          if (keys.includes(key.name)) {
            this.pressedKeys.add(action);
          }
        }
      }
    });

    // Enable input
    this.screen.enableInput();
    this.screen.enableMouse();
  }

  clear() {
    this.gameBox.setContent('');
    this.screen.render();
  }

  write(content, x, y, color = 'white') {
    const text = blessed.text({
      parent: this.gameBox,
      content: content,
      top: y,
      left: x,
      style: {
        fg: color
      }
    });
    this.screen.render();
  }

  getScreen() {
    return this.screen;
  }

  setColor(color) {
    this.currentColor = this.colors[color] || color;
  }

  setCursorPosition(x, y) {
    this.screen.program.cup(y, x);
    this.screen.render();
  }

  async isKeyPressed(key) {
    const isPressed = this.pressedKeys.has(key);
    if (isPressed) {
      // Clear the key after checking to prevent key "sticking"
      this.pressedKeys.delete(key);
    }
    return isPressed;
  }

  getWidth() {
    return this.screen.width;
  }

  getHeight() {
    return this.screen.height;
  }

  cleanup() {
    console.log('Cleaning up terminal');
    if (this.screen) {
      this.screen.destroy();
    }
  }

  render() {
    this.screen.render();
  }
} 