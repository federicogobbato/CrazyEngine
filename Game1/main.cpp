#pragma once

#define GLEW_STATIC

#include <iostream>
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
		window->processEvent();

		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		window->calculateDeltaTime();
		window->calculateFPS();
		//window->showFPS();

		game->update();
		SDL_GL_SwapWindow(window->getSDLWindow());
	}

	delete game;
	window->quitSystem();

	return 0;
}