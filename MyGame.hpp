#pragma once

#include <mu/core/Game.hpp>
#include <SDL2/SDL_events.h>

class MyGame : public mu::Game {
public:
    virtual void on_start();
    virtual void on_update();
    virtual void on_stop();
    virtual void on_keydown(SDL_KeyboardEvent const &key);
    virtual void on_keyup(SDL_KeyboardEvent const &key);
};

