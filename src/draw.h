#include "zstd.h"
#include "object.h"
void ClearBackground(SDL_Color color);
void DrawRectangle(int x, int y, int h, int w, SDL_Color color);
void DrawText(const char* text, int x, int y, SDL_Color color);
void DrawCircle(int x, int y, int radius, SDL_Color color);
void DrawFilledCircle(int x0, int y0, int radius, SDL_Color color);

void DrawObject(Object obj);

void BeginDrawing();
void EndDrawing();
float GetDrawTime();
