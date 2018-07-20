
#include <Engine\WindowSDL.h>
#include "PathFinding.h"

int main(int argc, char* argv[]) {

    Engine::Window* window = new Engine::WindowSDL();

    window->initSystem();

    Engine::GameSingleton<PathFinding>* game = new PathFinding();
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