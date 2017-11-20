#pragma once

#define GLEW_STATIC

#include <iostream>
#include <Engine\Window.h>
#include "Test.h"

#define NUMTEST 5

int main(int argc, char* argv[]) {

    std::cout << "Number of the test: [1-" << NUMTEST << "]" << std::endl;

	Engine::Window* window = Engine::Window::getWindow();

	window->initSystem();

    int test = 0;
    do {
        std::cin >> test;
    } while (test <= 0 && test > NUMTEST);   

    Test* currentTest = Test::chooseTest(test);

    currentTest->Init();

    while (window->getGameState() != Engine::GameState::QUIT) {
        window->processEvent();

		glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		window->calculateDeltaTime();
		window->calculateFPS();
		//window->showFPS();
        currentTest->draw();

        SDL_GL_SwapWindow(window->getSDLWindow());
    }

    window->quitSystem();

    return 0;
}