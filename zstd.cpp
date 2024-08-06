// vec.h
typedef struct Vector2 {
    float x, y;
} Vector2;

Vector2 operator+(Vector2 a, Vector2 b);


Vector2& operator+=(Vector2& a, const Vector2& b);

Vector2 operator+(Vector2 a, Vector2 b) {
    Vector2 c = {
        a.x + b.x,
        a.y + b.y
    };
    return c;
}

Vector2& operator+=(Vector2& a, const Vector2& b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstdio>
#define ERROR(fmt, ...) fprintf(stderr, "[ERROR] %s: " fmt "\n", __FUNCTION__, ##__VA_ARGS__);exit(1)


void InitWindow(int width, int height, const char* title);
void InitWindowFullscreen(const char* title);

void CloseWindow();
void PoolEvents();

bool WindowShouldClose();

float GetScreenWidth();
float GetScreenHeight();

SDL_Window *GetWindowReference();
SDL_Renderer *GetRendererReference();
typedef struct KeyBoardKey {
    int key;
    bool state;
} KeyBoardKey;

// Enum for keyboard keys, similar to raylib style
enum KeyboardKey {
    KEY_UNKNOWN = -1,
    KEY_A = SDLK_a,
    KEY_B = SDLK_b,
    KEY_C = SDLK_c,
    KEY_D = SDLK_d,
    KEY_E = SDLK_e,
    // Add more keys as needed
    KEY_F = SDLK_f,
    KEY_G = SDLK_g,
    KEY_H = SDLK_h,
    KEY_I = SDLK_i,
    KEY_J = SDLK_j,
    KEY_K = SDLK_k,
    KEY_L = SDLK_l,
    KEY_M = SDLK_m,
    KEY_N = SDLK_n,
    KEY_O = SDLK_o,
    KEY_P = SDLK_p,
    KEY_Q = SDLK_q,
    KEY_R = SDLK_r,
    KEY_S = SDLK_s,
    KEY_T = SDLK_t,
    KEY_U = SDLK_u,
    KEY_V = SDLK_v,
    KEY_W = SDLK_w,
    KEY_X = SDLK_x,
    KEY_Y = SDLK_y,
    KEY_Z = SDLK_z,
    KEY_0 = SDLK_0,
    KEY_1 = SDLK_1,
    KEY_2 = SDLK_2,
    KEY_3 = SDLK_3,
    KEY_4 = SDLK_4,
    KEY_5 = SDLK_5,
    KEY_6 = SDLK_6,
    KEY_7 = SDLK_7,
    KEY_8 = SDLK_8,
    KEY_9 = SDLK_9,
    // Add more keys as needed
    KEY_ESC = SDLK_ESCAPE,
    KEY_ENTER = SDLK_RETURN,
    KEY_SPACE = SDLK_SPACE,
    KEY_LEFT = SDLK_LEFT,
    KEY_RIGHT = SDLK_RIGHT,
    KEY_UP = SDLK_UP,
    KEY_DOWN = SDLK_DOWN,
    // Add more keys as needed
};

bool IsKeyDown(int key);
void UpdateKeyboardState(SDL_Event event);
SDL_Window * window = nullptr;
SDL_Renderer* renderer = nullptr;
bool shouldCloseWindow = false;

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
#include <SDL2/SDL_pixels.h>
typedef struct Object
{
	Vector2 pos;
	Vector2 size;
	SDL_Color color;
}Object;
void ClearBackground(SDL_Color color);
void DrawRectangle(int x, int y, int h, int w, SDL_Color color);
void DrawText(const char* text, int x, int y, SDL_Color color);


void DrawObject(Object obj);

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

void DrawRectangle(int x, int y, int w, int h, SDL_Color color){
	SDL_Renderer* renderer = GetRendererReference();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x,y,w,h};
    SDL_RenderFillRect(renderer, &rect);
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
#include <SDL2/SDL_keycode.h>
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
