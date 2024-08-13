#ifndef ZSTD_HPP
#define ZSTD_HPP

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


typedef struct Object {
  Vector2 pos;
  Vector2 size;
  Color color;
  void show(){
    DrawRectangleV(pos,size,color);
  }
} Object;

class Player : public Entity {
public:
  using Entity::Entity;
  void move(float dt) {
    this->pos.x += (IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * 200 * dt;
    this->pos.y += (IsKeyDown(KEY_S) - IsKeyDown(KEY_W)) * 200 * dt;
  }
};


typedef struct Cam {
    Camera2D cam;  // Camera2D struct from Raylib
    Vector2 pos;
    Vector2 offset;
    float rotation;
    float zoom;

    // Constructor to initialize the camera properties
    Cam(Vector2 pos, Vector2 offset, float rotation, float zoom) {
        this->pos = pos;
        this->offset = offset;
        this->rotation = rotation;
        this->zoom = zoom;
        this->cam = { pos, offset, rotation, zoom };
    }

    // Method to set the offset and update the camera
    void setOffset(Vector2 offset) {
        this->offset = offset;
    }

    // Method to focus the camera on a specific position
    void focus(Vector2 pos) {
        this->pos = pos;
    }

    // Method to apply offsets, position, zoom, rotation, and start the 2D camera mode
    void start() {
        // Apply the current values to the Camera2D struct
        this->cam.target = this->pos;
        this->cam.offset = this->offset;
        this->cam.rotation = this->rotation;
        this->cam.zoom = this->zoom;

        BeginMode2D(this->cam);
    }

    // Method to stop the 2D camera mode
    void stop() {
        EndMode2D();
    }
} Cam;

#endif // ZSTD_HPP
