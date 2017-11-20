#pragma once

#define GLEW_STATIC

#include "Arkanoid.h"
#include <Engine\Window.h>

int main(int argc, char* argv[]) {

    Engine::Window* window = Engine::Window::getWindow();

    window->initSystem();

    Arkanoid* game = new Arkanoid();
    game->run();

    while (window->getGameState() != Engine::GameState::QUIT) {

        Engine::Window::getWindow()->processEvent();

        // Set the base depth to 1.0
        glClearDepth(1.0);
        // Clear the color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window->calculateFrameTime();
        window->calculateFPS();
        window->showFPS();

        game->gameLoop();
        // Swap our buffer and draw everything to the screen
        window->swapBuffer();
    }

    delete game;
    window->quitSystem();

    return 0;
}