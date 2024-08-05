#include <SDL2/SDL_pixels.h>
#include <cstdio>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL.h>
#ifndef ZSTD_H
#define ZSTD_H

// vec.h
typedef struct Vec2 {
    float x, y;
} Vec2;

Vec2 operator+(Vec2 a, Vec2 b) {
    Vec2 c = {
        a.x + b.x,
        a.y + b.y
    };
    return c;
}

Vec2& operator+=(Vec2& a, const Vec2& b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

#define ERROR(fmt, ...) fprintf(stderr, "[ERROR] %s: " fmt "\n", __FUNCTION__, ##__VA_ARGS__);exit(1)


void CreateWindow(int width, int height, const char* title);
void CloseWindow();
void PoolEvents();

bool WindowShouldClose();

float GetScreenWidth();
float GetScreenHeight();

SDL_Window *GetWindowReference();
SDL_Renderer *GetRendererReference();

void ClearBackground(SDL_Color color);
void DrawRectangle(int x, int y, int h, int w, SDL_Color color);


void BeginDrawing();
void EndDrawing();
float GetDrawTime();

typedef struct KeyBoardKey{
	int key;
	bool state;
}KeyBoardKey;

bool IsKeyDown(int key);
void UpdateKeyboardState(SDL_Event event);


#endif // ZSTD_H
