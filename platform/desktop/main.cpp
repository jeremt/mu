#include <SDL2/SDL.h>
#include <mu/core/Game.hpp>
#include <MyGame.hpp>

int main() {
    mu::Game *game = new MyGame();
    SDL_Init(SDL_INIT_VIDEO);
    game->start();
    while (game->is_running()) {
        game->update();
    }
    game->stop();
    return 0;
}
