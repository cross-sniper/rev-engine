#include "Image.h"
#include "zstd.h"
#include <SDL2/SDL_error.h>
#include <string>


Image loadImage(const char* filePath) {
    Image img;
    printf("loading %s\n",filePath);

    // Initialize SDL_image
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        ERROR("Failed to initialize SDL_image: %s",IMG_GetError());
    }

    // Load the image file
    img.surface = IMG_Load(filePath);
    if (!img.surface) {
        ERROR("Failed to load image: %s",IMG_GetError());
    }

    // Set width and height
    img.width = img.surface->w;
    img.height = img.surface->h;

    // Clean up SDL_image
    IMG_Quit();

    return img;
}

void drawImage(Image img, int x, int y){
    SDL_Renderer *renderer = GetRendererReference();
}

void drawImage(const Image& img, int x, int y) {
    SDL_Renderer* renderer = GetRendererReference();

    // Check if the image has a valid surface
    if (img.surface == nullptr) {
        return; // or handle the error appropriately
    }

    // Create an SDL_Texture from the SDL_Surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img.surface);
    if (!texture) {
        // Handle texture creation failure
        return; // or log the error
    }

    // Define the destination rectangle
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = img.surface->w;
    destRect.h = img.surface->h;

    // Render the texture to the screen
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);

    // Clean up
    SDL_DestroyTexture(texture);
}
