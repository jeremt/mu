#include <iostream>
#include "MyGame.hpp"

void MyGame::on_start() {

}

void MyGame::on_update() {
    glClearColor(0.2f, 0.26f, 0.35f, 1.0f);
}

void MyGame::on_stop() {

}

void MyGame::on_keydown(SDL_KeyboardEvent const &key) {
    if (key.keysym.sym == SDLK_UP) {
        std::cout << "Coucou" << std::endl;
    }
}

void MyGame::on_keyup(SDL_KeyboardEvent const &) {

}