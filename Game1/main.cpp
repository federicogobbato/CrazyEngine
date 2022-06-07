#pragma once

#define GLEW_STATIC

#include <Engine\Window.h>
#include <Engine\WindowOPENGL.h>
#include "GameTest1.h"

int main(int argc, char* argv[]) {

	Engine::Window* window = new Engine::WindowOPENGL();

	window->initSystem();

	int difficulty=4;

	//std::cout << "Set difficulty [1-4]" << std::endl;
	//std::cin >> difficulty;

    Engine::Game* game = new GameTest1(difficulty);
	game->init();
    std::cout << "Game Start" << std::endl;

	while (window->processEvent() && window->getGameState() != Engine::GameState::QUIT)
	{
		// If enabled, do depth comparisons and update the depth buffer.
		glEnable(GL_DEPTH_TEST);
		window->clearRenderer();
		window->calculateFrameTime();
		window->calculateFPS();
		window->showFPS();
		game->update();
		// Swap our buffer and draw everything to the screen
		window->swapBuffer();	
	}

	delete dynamic_cast<GameTest1*>(game);
    delete dynamic_cast<Engine::WindowOPENGL*>(window);
    return 0;
}