#include <raylib.h>

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
