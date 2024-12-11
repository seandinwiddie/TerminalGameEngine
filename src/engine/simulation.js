import { Terminal } from './terminal.js';
import { UIPrinter } from './uiPrinter.js';

export class Simulation {
  static #instance = null;

  constructor() {
    if (Simulation.#instance) {
      return Simulation.#instance;
    }
    
    this.terminal = Terminal.getInstance();
    this.entities = new Set();
    this.uiPrinter = new UIPrinter(this.terminal);
    
    Simulation.#instance = this;
  }

  static getInstance() {
    if (!Simulation.#instance) {
      Simulation.#instance = new Simulation();
    }
    return Simulation.#instance;
  }

  loadLevel(level) {
    this.entities.clear();
    level.loadInSimulation();
  }

  tryAddEntity(entity) {
    this.entities.add(entity);
  }

  step() {
    // Clear screen
    this.terminal.clear();
    
    // Update and render all entities
    for (const entity of this.entities) {
      if (entity.update) {
        entity.update();
      }
      if (entity.render) {
        const pos = entity.position;
        this.terminal.write(entity.render(), pos.x, pos.y);
      }
    }
  }

  getUIPrinter() {
    return this.uiPrinter;
  }
} 