#pragma once

#include <mu/core/GL.hpp>
#include <SDL2/SDL.h>
#include <string>

namespace mu {

    class Game {
    public:
        Game();
        virtual ~Game() {}

    public:
        bool is_running() const { return _is_running; }

    public:
        virtual void on_start() = 0;
        virtual void on_update() = 0;
        virtual void on_stop() = 0;
        virtual void on_keydown(SDL_KeyboardEvent const &key) = 0;
        virtual void on_keyup(SDL_KeyboardEvent const &key) = 0;

    public:
        void start();
        void update();
        void stop();

    private:
        bool _is_running;
        SDL_Window *_sdl_window;
    };

}