#include <emscripten/emscripten.h>
#include <MyGame.hpp>

static mu::Game *game;

int main() {
    game = new MyGame();
    game->start();
    emscripten_set_main_loop([] {
        game->update();
    }, 0, true);
    game->stop();
    delete game;
    return 0;
}
