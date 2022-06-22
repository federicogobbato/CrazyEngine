#pragma once

#define GLEW_STATIC

#include "Arkanoid.h"
#include <Engine\WindowOPENGL.h>

int main(int argc, char* argv[]) {

    Engine::Window* window = new Engine::WindowOPENGL();

    window->initSystem();

    window->disableVSync();

    Engine::Game* game = new Arkanoid();
    game->init();

    while (window->getGameState() != Engine::GameState::QUIT)
    {
        window->calculateFixedDeltaTime();
        window->clearRenderer();
        game->update();
        window->showFPS();
    }

    delete game;
    delete window;

    return 0;
}