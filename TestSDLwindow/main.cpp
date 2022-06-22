

#include <Engine\WindowSDL.h>
#include "TestWindow.h"

int main(int argc, char* argv[]) {

	Engine::Window* window = new Engine::WindowSDL();

	window->initSystem();

	TestWindow* game = new TestWindow();
	game->init();

	while (window->getGameState() != Engine::GameState::QUIT) {

		window->startCalculateFPS();
		if (window->processEvent())
		{
			game->update();
		}
		window->showFPS();
	}

	window->quitSystem();

	return 0;
}
