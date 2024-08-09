#include "zstd.h"

// Define the Image struct to match your needs
struct Image {
    SDL_Surface* surface;
    int width;
    int height;
};

Image loadImage(const char* filePath);
void drawImage(const Image& img, int x, int y);
