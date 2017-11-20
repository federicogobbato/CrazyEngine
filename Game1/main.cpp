#pragma once

#define GLEW_STATIC

#include <Engine\Window.h>
#include "Game.h"

int main(int argc, char* argv[]) {

	Engine::Window* window = Engine::Window::getWindow();

	window->initSystem();

	int difficulty;

	std::cout << "Set difficulty [1-4]" << std::endl;
	std::cin >> difficulty;

	Game* game = new Game(difficulty);
	game->init();

	while (window->getGameState() != Engine::GameState::QUIT) {

        Engine::Window::getWindow()->processEvent();

        // If enabled, do depth comparisons and update the depth buffer.
		glEnable(GL_DEPTH_TEST);
        // Clear the color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		window->calculateFrameTime();
		window->calculateFPS();
		//window->showFPS();

		game->update();
        // Swap our buffer and draw everything to the screen
        window->swapBuffer(); 
	}

	delete game;
	window->quitSystem();

	return 0;
}