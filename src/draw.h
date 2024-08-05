#include "zstd.h"
#include "object.h"
void ClearBackground(SDL_Color color);
void DrawRectangle(int x, int y, int h, int w, SDL_Color color);
void DrawObject(Object obj, SDL_Color color);

void BeginDrawing();
void EndDrawing();
float GetDrawTime();
