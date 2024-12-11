export class Level {
  constructor() {
    this.terminated = false;
    this.worldSizeX = process.stdout.columns || 80;
    this.worldSizeY = process.stdout.rows || 24;
    this.screenPadding = 1;
  }

  loadInSimulation() {
    // To be implemented by child classes
  }

  isTerminated() {
    return this.terminated;
  }

  terminate() {
    this.terminated = true;
  }

  getWorldSizeX() {
    return this.worldSizeX;
  }

  getWorldSizeY() {
    return this.worldSizeY;
  }

  getScreenPadding() {
    return this.screenPadding;
  }

  onGameOver() {
    // To be implemented by child classes
  }

  onPostGameOverDelayEnded() {
    // To be implemented by child classes
  }
} 