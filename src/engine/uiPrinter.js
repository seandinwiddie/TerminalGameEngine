export class UIPrinter {
  constructor(terminal) {
    this.terminal = terminal;
  }

  printOnHeader(text, x, color) {
    this.terminal.write(text, x, 1, color);
  }

  printWindow(window, color, position = 'center') {
    // Implementation for window printing
    // This will be needed for game over screens
    const content = window.toString();
    const lines = content.split('\n');
    const width = Math.max(...lines.map(line => line.length));
    const height = lines.length;
    
    let startX = 0;
    let startY = 0;

    switch(position) {
      case 'centerX_topY':
        startX = Math.floor((this.terminal.getWidth() - width) / 2);
        startY = 2;
        break;
      default: // center
        startX = Math.floor((this.terminal.getWidth() - width) / 2);
        startY = Math.floor((this.terminal.getHeight() - height) / 2);
    }

    lines.forEach((line, i) => {
      this.terminal.write(line, startX, startY + i, color);
    });
  }
} 