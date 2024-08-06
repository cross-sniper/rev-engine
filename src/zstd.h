#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstdio>
#define ERROR(fmt, ...) fprintf(stderr, "[ERROR] %s: " fmt "\n", __FUNCTION__, ##__VA_ARGS__);exit(1)


void InitWindow(int width, int height, const char* title);
void InitWindowFullscreen(const char* title);

void CloseWindow();
void PoolEvents();

bool WindowShouldClose();

float GetScreenWidth();
float GetScreenHeight();

SDL_Window *GetWindowReference();
SDL_Renderer *GetRendererReference();
