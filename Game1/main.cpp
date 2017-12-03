#pragma once

#define GLEW_STATIC

#include <Engine\Window.h>
#include <Engine\WindowOPENGL.h>
#include "GameTest1.h"

int main(int argc, char* argv[]) {

	Engine::Window* window = new Engine::WindowOPENGL();

	window->initSystem();

	int difficulty;

	std::cout << "Set difficulty [1-4]" << std::endl;
	std::cin >> difficulty;

    Engine::Game* game = new GameTest1(difficulty);
	game->init();

	while (window->getGameState() != Engine::GameState::QUIT) {

        window->processEvent();

        // If enabled, do depth comparisons and update the depth buffer.
        glEnable(GL_DEPTH_TEST);
        window->clearRenderer();

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