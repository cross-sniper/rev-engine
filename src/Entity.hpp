#include <raylib.h>

class Entity {
public:
  Vector2 pos;
  Vector2 size;
  Color color;

  Entity(Vector2 pos = {0, 0}, Vector2 size = {0, 0}, Color color = BLACK) {

    this->pos = pos;
    this->size = size;
    this->color = color;
  }

  void draw() { DrawRectangleV(this->pos, this->size, this->color); }

  void move(float dt);
};

