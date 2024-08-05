#include "zstd.h"
typedef struct KeyBoardKey{
	int key;
	bool state;
}KeyBoardKey;

bool IsKeyDown(int key);
void UpdateKeyboardState(SDL_Event event);
