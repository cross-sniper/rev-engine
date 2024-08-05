#include "draw.h"
#include "zstd.h"
#include <SDL2/SDL_render.h>

float dt = 0;
float lastTime = 0;

void ClearBackground(SDL_Color color) {
    SDL_Renderer* renderer = GetRendererReference();
    // Set the drawing color (background color)
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    // Clear the current rendering target with the drawing color
    SDL_RenderClear(renderer);
}

void BeginDrawing() {
    // Get the current time in milliseconds
    float currentTime = SDL_GetTicks() / 1000.0f;
    dt = currentTime - lastTime;
    lastTime = currentTime;
}

void EndDrawing() {
    SDL_Renderer* renderer = GetRendererReference();
    SDL_RenderPresent(renderer);
    PoolEvents();
}

void DrawRectangle(int x, int y, int h, int w, SDL_Color color){
	SDL_Renderer* renderer = GetRendererReference();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x,y,w,h};
    SDL_RenderFillRect(renderer, &rect);
}

float GetDrawTime() {
    return dt;
}
