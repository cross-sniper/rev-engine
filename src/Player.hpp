#include "Entity.hpp"

class Player : public Entity {
public:
  using Entity::Entity;
  void move(float dt) {
    this->pos.x += (IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * 200 * dt;
    this->pos.y += (IsKeyDown(KEY_S) - IsKeyDown(KEY_W)) * 200 * dt;
  }
};

