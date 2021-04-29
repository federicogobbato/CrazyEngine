
#include <Engine\WindowSDL.h>
#include "PathFinding.h"

int main(int argc, char* argv[]) {

	Engine::Window* window = new Engine::WindowSDL();

	window->initSystem();

	Engine::TSingleton<PathFinding>* game = new PathFinding();
	game->GetSingleton()->init();

	while (window->getGameState() != Engine::GameState::QUIT) {

		window->processEvent();

		window->calculateFPS();
		window->showFPS();

		game->GetSingleton()->update();
	}

	window->quitSystem();

	return 0;
}