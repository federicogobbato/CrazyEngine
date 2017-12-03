#define GLEW_STATIC

#include <Engine\Window.h>

#include "PathFinding.h"

int main(int argc, char* argv[]) {

    Engine::Window* window = Engine::Window::GetSingleton();

    window->initSystem(1280, 720, 60, "PathFinding", Engine::SDL_Flags::SDL_RENDERER);

    Engine::Game* game = new PathFinding();

    game->init();

    while (window->getGameState() != Engine::GameState::QUIT) {

        window->processEvent();

        window->calculateFPS();
        window->showFPS();

        game->update();

    }

    window->quitSystem();

    return 0;
}