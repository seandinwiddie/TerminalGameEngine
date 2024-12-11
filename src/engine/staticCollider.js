import { EventEmitter } from 'events';

export class StaticCollider {
  constructor(xPos, yPos, sizeX, sizeY, modelChar) {
    this.x = xPos;
    this.y = yPos;
    this.width = sizeX;
    this.height = sizeY;
    this.modelChar = modelChar;
    this.events = new EventEmitter();
    this.sortingLayer = 0;
  }

  update() {
    // Static colliders don't need updating
  }

  render() {
    const line = this.modelChar.repeat(this.width);
    for (let i = 0; i < this.height; i++) {
      process.stdout.cursorTo(this.x, this.y + i);
      process.stdout.write(line);
    }
  }

  onCollisionEnter(other) {
    this.events.emit('collision', other);
  }

  getPosition() {
    return { x: this.x, y: this.y };
  }

  getSize() {
    return { width: this.width, height: this.height };
  }

  getSortingLayer() {
    return this.sortingLayer;
  }

  setSortingLayer(layer) {
    this.sortingLayer = layer;
  }
} 