#include "draw.h"
#include <SDL2/SDL_pixels.h>
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

void DrawRectangle(int x, int y, int w, int h, SDL_Color color){
	SDL_Renderer* renderer = GetRendererReference();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x,y,w,h};
    SDL_RenderFillRect(renderer, &rect);
}
void DrawFilledCircle(int x0, int y0, int radius, SDL_Color color) {
    SDL_Renderer* renderer = GetRendererReference();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
            }
        }
    }
}

void DrawCircle(int x, int y, int radius, SDL_Color color) {
    SDL_Renderer* renderer = GetRendererReference();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int dx = 0;
    int dy = radius;
    int d = 1 - radius;

    // Draw the initial point
    SDL_RenderDrawPoint(renderer, x + dx, y + dy);
    SDL_RenderDrawPoint(renderer, x - dx, y + dy);
    SDL_RenderDrawPoint(renderer, x + dx, y - dy);
    SDL_RenderDrawPoint(renderer, x - dx, y - dy);
    SDL_RenderDrawPoint(renderer, x + dy, y + dx);
    SDL_RenderDrawPoint(renderer, x - dy, y + dx);
    SDL_RenderDrawPoint(renderer, x + dy, y - dx);
    SDL_RenderDrawPoint(renderer, x - dy, y - dx);

    while (dx < dy) {
        dx++;
        if (d < 0) {
            d += 2 * dx + 1;
        } else {
            dy--;
            d += 2 * (dx - dy) + 1;
        }
        
        // Draw points on the circle
        SDL_RenderDrawPoint(renderer, x + dx, y + dy);
        SDL_RenderDrawPoint(renderer, x - dx, y + dy);
        SDL_RenderDrawPoint(renderer, x + dx, y - dy);
        SDL_RenderDrawPoint(renderer, x - dx, y - dy);
        SDL_RenderDrawPoint(renderer, x + dy, y + dx);
        SDL_RenderDrawPoint(renderer, x - dy, y + dx);
        SDL_RenderDrawPoint(renderer, x + dy, y - dx);
        SDL_RenderDrawPoint(renderer, x - dy, y - dx);
    }
}

void DrawObject(Object obj){
    DrawRectangle(obj.pos.x,obj.pos.y, obj.size.x, obj.size.y, obj.color);
}

void DrawText(const char* text, int x, int y, SDL_Color color){
    SDL_Renderer* renderer = GetRendererReference();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

}

float GetDrawTime() {
    return dt;
}
