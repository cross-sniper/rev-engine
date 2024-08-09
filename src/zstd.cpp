#include "zstd.h"
#include "keyboard.h"
#include <SDL2/SDL_video.h>
SDL_Window * window = nullptr;
SDL_Renderer* renderer = nullptr;
bool shouldCloseWindow = false;
int exitKey = SDLK_ESCAPE;

void InitWindowFullscreen(const char* title){
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	if(not window){
		printf("something went wrong while creating the window: %s\n", SDL_GetError());
		exit(1);
	}
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	if(not renderer){
		printf("something went wrong while creating the renderer: %s\n", SDL_GetError());
		exit(1);
	}
}

void InitWindow(int width, int height, const char *title){
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if(not window){
		printf("something went wrong while creating the window: %s\n", SDL_GetError());
		exit(1);
	}
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	if(not renderer){
		printf("something went wrong while creating the renderer: %s\n", SDL_GetError());
		exit(1);
	}
}

void CloseWindow(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

float GetScreenWidth() {
    if (window) {
        int width;
        SDL_GetWindowSize(window, &width, nullptr);
        return static_cast<float>(width);
    }
    return 0.0f;
}

float GetScreenHeight() {
    if (window) {
        int height;
        SDL_GetWindowSize(window, nullptr, &height);
        return static_cast<float>(height);
    }
    return 0.0f;
}


// this can be used by other stuff
SDL_Window* GetWindowReference(){
	if(not window){
		ERROR("did you initialize the window?");
	}
	return window;
}

SDL_Renderer* GetRendererReference(){
	if(not renderer){
		ERROR("did you initialize the window?");
	}
	return renderer;
}

bool WindowShouldClose(){
	if(not window){
		ERROR("did you initialize the window?");
	}

	return shouldCloseWindow;
}

void SetExitKey(int key)
{
	exitKey = key;
}

void PoolEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
            	shouldCloseWindow = true;
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            	if(event.key.keysym.sym == exitKey){
            		shouldCloseWindow = true;
            	}
            	UpdateKeyboardState(event);
            	UpdatePreviousKeyboardState();
            	break;
            // Handle other events here
            default:
                break;
        }
    }
}
