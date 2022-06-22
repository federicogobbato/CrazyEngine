#pragma once

#define GLEW_STATIC

#include <Engine\Window.h>
#include <Engine\WindowOPENGL.h>
#include "GameTest1.h"

int main(int argc, char* argv[]) {

	Engine::Window* window = new Engine::WindowOPENGL();

	window->initSystem();

	window->disableVSync();

	int difficulty=4;

	//std::cout << "Set difficulty [1-4]" << std::endl;
	//std::cin >> difficulty;

    Engine::Game* game = new GameTest1(difficulty);
	game->init();
    std::cout << "Game Start" << std::endl;

	// If enabled, do depth comparisons and update the depth buffer
	glEnable(GL_DEPTH_TEST);

	while (window->getGameState() != Engine::GameState::QUIT)
	{
		window->calculateFixedDeltaTime();
		window->clearRenderer();
		game->update();
		window->showFPS();
	}

	delete game;
	delete window;
    return 0;
}