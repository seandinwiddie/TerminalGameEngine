class CollisionSystem {
  constructor() {
    this.colliders = new Set();
  }

  addCollider(gameObject) {
    this.colliders.add(gameObject);
  }

  checkCollisions() {
    for (const obj1 of this.colliders) {
      for (const obj2 of this.colliders) {
        if (obj1 === obj2) continue;
        
        if (this.isColliding(obj1, obj2)) {
          obj1.onCollisionEnter(obj2);
          obj2.onCollisionEnter(obj1);
        }
      }
    }
  }

  isColliding(a, b) {
    return (a.x < b.x + b.width &&
            a.x + a.width > b.x &&
            a.y < b.y + b.height &&
            a.y + a.height > b.y);
  }
} 