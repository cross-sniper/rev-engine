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
#include <SDL2/SDL_image.h>

#include <cstdio>
#define ERROR(fmt, ...) fprintf(stderr, "[ERROR] %s: " fmt "\n", __FUNCTION__, ##__VA_ARGS__);exit(1)
#ifdef DEBUG_LOG_ENABLED
#define DEBUGLOG(fmt, ...) fprintf(stderr, "[ERROR] %s:%d:\n\t%s: " fmt "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define DEBUGLOG(fmt, ...)
#endif


void InitWindow(int width, int height, const char* title);
void InitWindowFullscreen(const char* title);

void CloseWindow();
void PoolEvents();

bool WindowShouldClose();

float GetScreenWidth();
float GetScreenHeight();

void SetExitKey(int key);

SDL_Window *GetWindowReference();
SDL_Renderer *GetRendererReference();
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
void DrawCircle(int x, int y, int radius, SDL_Color color);
void DrawFilledCircle(int x0, int y0, int radius, SDL_Color color);

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
bool IsKeyUp(int key);
bool IsKeyPressed(int key);
void UpdateKeyboardState(SDL_Event event);
#include <SDL2/SDL_keycode.h>
#include <iostream>

#define MAX_KEYBOARD_KEYS 256
static KeyBoardKey keyboardKeys[MAX_KEYBOARD_KEYS];
static KeyBoardKey LastKeyboardKeys[MAX_KEYBOARD_KEYS];

bool IsKeyUp(int key) {
    if (key < 0 || key >= MAX_KEYBOARD_KEYS) return false;
    return !keyboardKeys[key].state;
}

bool IsKeyDown(int key) {
    if (key < 0 || key >= MAX_KEYBOARD_KEYS) return false;
    return keyboardKeys[key].state;
}

bool IsKeyPressed(int key) {
    if (key < 0 || key >= MAX_KEYBOARD_KEYS) return false;
    // Key is pressed if current state is true and previous state was false
    bool pressed = (keyboardKeys[key].state && !LastKeyboardKeys[key].state);
    if (pressed) {
        DEBUGLOG("Key %i pressed\n", key);
    }
    return pressed;
}

void UpdateKeyboardState(SDL_Event event) {
    int key = event.key.keysym.sym;

    if (key < 0 || key >= MAX_KEYBOARD_KEYS) return; // Ignore out-of-range keys

    if (event.type == SDL_KEYDOWN) {
        keyboardKeys[key].key = key;
        keyboardKeys[key].state = true;
        DEBUGLOG("Key %i down\n", key);
    } else if (event.type == SDL_KEYUP) {
        keyboardKeys[key].key = key;
        keyboardKeys[key].state = false;
        DEBUGLOG("Key %i up\n", key);
    }
}

void UpdatePreviousKeyboardState() {
    for (int i = 0; i < MAX_KEYBOARD_KEYS; ++i) {
        if (LastKeyboardKeys[i].state != keyboardKeys[i].state) {
            DEBUGLOG("Key %i state changed: %d -> %d\n",
                     i, LastKeyboardKeys[i].state, keyboardKeys[i].state);
        }
        LastKeyboardKeys[i].state = keyboardKeys[i].state;
    }
}
Vector2 getMousePos(){
	SDL_Window* win = GetWindowReference();
    if (!win) {
    	ERROR("no window was able to be found\n");
    }
    int x, y;
    SDL_GetMouseState(&x, &y); // Get the mouse position relative to the window

	return {float(x),float(y)};
}

// Define the Image struct to match your needs
struct Image {
    SDL_Surface* surface;
    int width;
    int height;
};

Image loadImage(const char* filePath);
void drawImage(const Image& img, int x, int y);
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
