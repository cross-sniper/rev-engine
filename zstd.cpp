#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <cstdio>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL.h>
#define ERROR(fmt, ...) fprintf(stderr, "[ERROR] %s: " fmt "\n", __FUNCTION__, ##__VA_ARGS__);exit(1)


void CreateWindow(int width, int height, const char* title);
void CloseWindow();
void PoolEvents();

bool WindowShouldClose();

float GetScreenWidth();
float GetScreenHeight();

SDL_Window *GetWindowReference();
SDL_Renderer *GetRendererReference();

typedef struct KeyBoardKey{
	int key;
	bool state;
}KeyBoardKey;

bool IsKeyDown(int key);
void UpdateKeyboardState(SDL_Event event);

SDL_Window * window = nullptr;
SDL_Renderer* renderer = nullptr;


bool shouldCloseWindow = false;


void CreateWindow(int width, int height, const char *title){
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

void PoolEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
            	shouldCloseWindow = true;
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            	if(event.key.keysym.sym == SDLK_ESCAPE){
            		shouldCloseWindow = true;
            	}
            	UpdateKeyboardState(event);
            	break;
            // Handle other events here
            default:
                break;
        }
    }
}

void ClearBackground(SDL_Color color);
void DrawRectangle(int x, int y, int h, int w, SDL_Color color);


void BeginDrawing();
void EndDrawing();
float GetDrawTime();


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

#define MAX_KEYBOARD_KEYS 256
static KeyBoardKey keyboardKeys[MAX_KEYBOARD_KEYS];


bool IsKeyDown(int key) {
    if (key < 0 || key >= MAX_KEYBOARD_KEYS) return false;
    return keyboardKeys[key].state;
}


void UpdateKeyboardState(SDL_Event event) {
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        int key = event.key.keysym.sym;
        bool state = (event.type == SDL_KEYDOWN);

        if (key >= 0 && key < MAX_KEYBOARD_KEYS) {
            keyboardKeys[key].key = key;
            keyboardKeys[key].state = state;
        }
    }
}

