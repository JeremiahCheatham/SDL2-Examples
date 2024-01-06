#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WINDOW_TITLE "03 Background"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define IMAGE_FLAGS IMG_INIT_PNG

struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *background;
};

bool sdl_initialize(struct Game *game);
bool load_media(struct Game *game); 
void game_cleanup(struct Game *game);

int main() {
    struct Game game = {
        .window = NULL,
        .renderer = NULL,
        .background = NULL,
    };

    if (sdl_initialize(&game)) {
        game_cleanup(&game);
    }

    if (load_media(&game)) {
        game_cleanup(&game);
    }

    while (true) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    game_cleanup(&game);
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_ESCAPE:
                            game_cleanup(&game);
                        default:
                            break;
                    }
                default:
                    break;
            }
        }

        // Update all objects here.

        // Clears the back screen buffer.
        SDL_RenderClear(game.renderer);

        // Do all your drawing here.
        SDL_RenderCopy(game.renderer, game.background, NULL, NULL);

        // Flips the front and back buffers, displays what has been drawn.
        SDL_RenderPresent(game.renderer);

        SDL_Delay(16);
    }

    game_cleanup(&game);

    return 0;
}

void game_cleanup(struct Game *game) {
    SDL_DestroyTexture(game->background);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    IMG_Quit();
    SDL_Quit();
    exit(0);
}

bool sdl_initialize(struct Game *game) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return true;
    }

    int img_init = IMG_Init(IMAGE_FLAGS);
    if ((img_init & IMAGE_FLAGS) != IMAGE_FLAGS) {
        fprintf(stderr, "Error initializing SDL_image: %s\n", IMG_GetError());
        return true;
    }

    game->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!game->window){
        fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
        return true;
    }

    game->renderer = SDL_CreateRenderer(game->window, -1, 0);
    if (!game->renderer){
        fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
        return true;
    }

    return false;
}

bool load_media(struct Game *game) {
    game->background = IMG_LoadTexture(game->renderer, "images/background.png");
    if (!game->background){
        fprintf(stderr, "Error creating a texture: %s\n", IMG_GetError());
        return true;
    }

    return false;
}
