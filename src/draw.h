#include <SDL2/SDL_pixels.h>
void ClearBackground(SDL_Color color);
void DrawRectangle(int x, int y, int h, int w, SDL_Color color);


void BeginDrawing();
void EndDrawing();
float GetDrawTime();
