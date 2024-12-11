import { GameLoop } from './engine/gameLoop.js';

async function main() {
  const gameLoop = new GameLoop();
  await gameLoop.start();
}

main().catch(console.error); 