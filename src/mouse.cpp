#include "mouse.h"// defines getMousePos, and inludes zstd(the sdl2-based game lib)
Vector2 getMousePos(){
	SDL_Window* win = GetWindowReference();
    if (!win) {
    	ERROR("no window was able to be found\n");
    }
    int x, y;
    SDL_GetMouseState(&x, &y); // Get the mouse position relative to the window

	return {float(x),float(y)};
}