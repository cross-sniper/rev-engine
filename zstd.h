#ifndef ZSTD_H
#define ZSTD_H

// vec.h
typedef struct Vector2 {
    float x, y;
} Vector2;

Vector2 operator+(Vector2 a, Vector2 b);


Vector2& operator+=(Vector2& a, const Vector2& b);
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>

#include <cstdio>
#define ERROR(fmt, ...) fprintf(stderr, "[ERROR] %s: " fmt "\n", __FUNCTION__, ##__VA_ARGS__);exit(1)
#ifdef DEBUG_LOG_ENABLED
#define DEBUGLOG(fmt, ...) fprintf(stderr, "[ERROR] %s:%d:\n\t%s: " fmt "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define DEBUGLOG(fmt, ...)
#endif


void InitWindow(int width, int height, const char* title);
void InitWindowFullscreen(const char* title);

void CloseWindow();
void PoolEvents();

bool WindowShouldClose();

float GetScreenWidth();
float GetScreenHeight();

void SetExitKey(int key);

SDL_Window *GetWindowReference();
SDL_Renderer *GetRendererReference();
#include <SDL2/SDL_pixels.h>
typedef struct Object
{
	Vector2 pos;
	Vector2 size;
	SDL_Color color;
}Object;
void ClearBackground(SDL_Color color);
void DrawRectangle(int x, int y, int h, int w, SDL_Color color);
void DrawText(const char* text, int x, int y, SDL_Color color);
void DrawCircle(int x, int y, int radius, SDL_Color color);
void DrawFilledCircle(int x0, int y0, int radius, SDL_Color color);

void DrawObject(Object obj);

void BeginDrawing();
void EndDrawing();
float GetDrawTime();
typedef struct KeyBoardKey {
    int key;
    bool state;
} KeyBoardKey;

// Enum for keyboard keys, similar to raylib style
enum KeyboardKey {
    KEY_UNKNOWN = -1,
    KEY_A = SDLK_a,
    KEY_B = SDLK_b,
    KEY_C = SDLK_c,
    KEY_D = SDLK_d,
    KEY_E = SDLK_e,
    // Add more keys as needed
    KEY_F = SDLK_f,
    KEY_G = SDLK_g,
    KEY_H = SDLK_h,
    KEY_I = SDLK_i,
    KEY_J = SDLK_j,
    KEY_K = SDLK_k,
    KEY_L = SDLK_l,
    KEY_M = SDLK_m,
    KEY_N = SDLK_n,
    KEY_O = SDLK_o,
    KEY_P = SDLK_p,
    KEY_Q = SDLK_q,
    KEY_R = SDLK_r,
    KEY_S = SDLK_s,
    KEY_T = SDLK_t,
    KEY_U = SDLK_u,
    KEY_V = SDLK_v,
    KEY_W = SDLK_w,
    KEY_X = SDLK_x,
    KEY_Y = SDLK_y,
    KEY_Z = SDLK_z,
    KEY_0 = SDLK_0,
    KEY_1 = SDLK_1,
    KEY_2 = SDLK_2,
    KEY_3 = SDLK_3,
    KEY_4 = SDLK_4,
    KEY_5 = SDLK_5,
    KEY_6 = SDLK_6,
    KEY_7 = SDLK_7,
    KEY_8 = SDLK_8,
    KEY_9 = SDLK_9,
    // Add more keys as needed
    KEY_ESC = SDLK_ESCAPE,
    KEY_ENTER = SDLK_RETURN,
    KEY_SPACE = SDLK_SPACE,
    KEY_LEFT = SDLK_LEFT,
    KEY_RIGHT = SDLK_RIGHT,
    KEY_UP = SDLK_UP,
    KEY_DOWN = SDLK_DOWN,
    // Add more keys as needed
};

bool IsKeyDown(int key);
bool IsKeyUp(int key);
bool IsKeyPressed(int key);
void UpdateKeyboardState(SDL_Event event);

#if defined(__cplusplus)
    #define CLITERAL(type)      type
#else
    #define CLITERAL(type)      (type)
#endif

#define LIGHTGRAY  CLITERAL(SDL_Color){ 200, 200, 200, 255 }   // Light Gray
#define RED CLITERAL(SDL_Color){255,0,0,255} // Red
#define GREEN CLITERAL(SDL_Color){0,255,0,255} // Green
#define BLUE CLITERAL(SDL_Color){0,0,255,255} // Blue

#define WHITE      CLITERAL(SDL_Color){ 255, 255, 255, 255 }   // White
#define BLACK      CLITERAL(SDL_Color){ 0, 0, 0, 255 }         // Black
#define BLANK      CLITERAL(SDL_Color){ 0, 0, 0, 0 }           // Blank (Transparent)
#define MAGENTA    CLITERAL(SDL_Color){ 255, 0, 255, 255 }     // Magenta

Vector2 getMousePos();

// Define the Image struct to match your needs
struct Image {
    SDL_Surface* surface;
    int width;
    int height;
};

Image loadImage(const char* filePath);
void drawImage(const Image& img, int x, int y);

#endif // ZSTD_H
