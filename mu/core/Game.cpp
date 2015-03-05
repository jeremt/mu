#include <mu/core/Game.hpp>

namespace mu {

    Game::Game() :
            _is_running(true),
            _sdl_window(nullptr) {
    }

    void Game::start() {
        SDL_Init(SDL_INIT_VIDEO);
        _sdl_window = SDL_CreateWindow(
                "hello",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                int(1.77 * 400),
                400,
                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
        );
        SDL_GL_CreateContext(_sdl_window);
        on_start();
    }

    void Game::update() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    stop();
                    break;
                case SDL_KEYDOWN:
                    on_keydown(event.key);
                    break;
                case SDL_KEYUP:
                    on_keyup(event.key);
                    break;
                default:
                    break;
            }
            if (event.type == SDL_QUIT) {
                stop();
                break;
            }
        }
        glClear(GL_COLOR_BUFFER_BIT);
        on_update();
        SDL_GL_SwapWindow(_sdl_window);
    }

    void Game::stop() {
        _is_running = false;
        on_stop();
        SDL_Quit();
    }

}