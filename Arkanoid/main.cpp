#pragma once

#define GLEW_STATIC

#include "Arkanoid.h"
#include <Engine\WindowOPENGL.h>

int main(int argc, char* argv[]) {

    Engine::Window* window = new Engine::WindowOPENGL();

    window->initSystem();

    //window->disableVSync();

    Engine::Game* game = new Arkanoid();
    game->init();

    while (window->processEvent() && window->getGameState() != Engine::GameState::QUIT)
    {
        window->clearRenderer();
        window->calculateFrameTime();
        window->calculateFPS();
        window->showFPS();
        game->update();
        window->swapBuffer();       
    }

    delete game;
    window->quitSystem();

    return 0;
}