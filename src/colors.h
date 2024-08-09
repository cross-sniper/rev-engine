#include <SDL2/SDL_pixels.h>

#if defined(__cplusplus)
    #define CLITERAL(type)      type
#else
    #define CLITERAL(type)      (type)
#endif

#define LIGHTGRAY  CLITERAL(SDL_Color){ 200, 200, 200, 255 }   // Light Gray
#define RED CLITERAL(SDL_Color){255,0,0,255} // Red
#define GREEN CLITERAL(SDL_Color){0,255,0,255} // Green
#define BLUE CLITERAL(SDL_Color){0,0,255,255} // Blue

#define WHITE      CLITERAL(SDL_Color){ 255, 255, 255, 255 }   // White
#define BLACK      CLITERAL(SDL_Color){ 0, 0, 0, 255 }         // Black
#define BLANK      CLITERAL(SDL_Color){ 0, 0, 0, 0 }           // Blank (Transparent)
#define MAGENTA    CLITERAL(SDL_Color){ 255, 0, 255, 255 }     // Magenta
