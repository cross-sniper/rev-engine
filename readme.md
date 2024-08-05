# zstdlib
*was rev-engine*

this is a game lib made arround sdl2, with function names similar to raylib's

## how to build the header and implementation
in the project, there is a "build.py", run it and it will automaticaly generate the `zstd.h` and `zstd.cpp`

```sh
python build.py
```

## how to use
```cpp
// includes the library
#include "zstd.h"
// makes a object that we use as the player
Object player = {
    {0,0},   // position - Vector2
    {20,20}, // size - Vector2
    RED      // color - SDL_Color
};

void move(float dt){
	// this is how we move the player,
	// IsKeyDown expects a int/SDLK(SDL Key), KEY_<name> is defined in a enum that are just "aliases" to SDLK_<name in lowercase>
    if(IsKeyDown(KEY_A)){
        player.pos.x -= 200 * dt;
    }else if(IsKeyDown(KEY_D)){
        player.pos.x += 200 * dt;
    }

    if(IsKeyDown(KEY_W)){
        player.pos.y -= 200 * dt;
    }else if(IsKeyDown(KEY_S)){
        player.pos.y += 200 * dt;
    }
}

int main(){
	// Creates a window with width 800, height 600, and title of "test"
	// currently we cannot make a full screen window that takes up all of the space when a given number is 0(like raylib), because i have no clue how to do that with sdl
    CreateWindow(800, 600, "test");
    //the main loop of the game
    // WindowShoudClose returns if we need to close the window,
    // e.g: has the player pressed the X button on title bar? or has the player pressed ESCAPE?
    // this is handled by PoolEvents, tigered by the EndDrawing
    while(!WindowShouldClose()){
    	// BeginDrawing, as of now, just calculates deltatime, that GetDrawTime returns
        BeginDrawing();
        ClearBackground(BLACK);
        float dt = GetDrawTime();
        move(dt);
        // you can also call
        // DrawObject(player);
        DrawRectangle(player.pos.x,player.pos.y,player.size.x,player.size.y,player.color);
        EndDrawing();
    }
    // Destroy the renderer, and window,
    // then quit sdl
    CloseWindow();

    return 0;
}

```


to compile it, you run:

```sh
g++ main.cpp -o main zstd.cpp -l SDL2
```
main.cpp is the name of your source file
main(after the -o) is the name of your binary
zstd.cpp is the library's implementation

