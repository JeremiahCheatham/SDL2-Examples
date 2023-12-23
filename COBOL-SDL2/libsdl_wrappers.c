#include "SDL2/SDL.h"

Uint8 get_sdl_keystate(Uint8 *keystate, int index) {
    return keystate[index];
}

int print_sdl_error(const char *message) {
    fprintf(stderr, "%s: %s\n", message, SDL_GetError());
    return 1;
}