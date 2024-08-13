#include <raylib.h>

typedef struct Object {
  Vector2 pos;
  Vector2 size;
  Color color;
  void show(){
    DrawRectangleV(pos,size,color);
  }
} Object;
