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
