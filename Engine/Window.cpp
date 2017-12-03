#include "Window.h"

#include <iostream>
#include <SDL_image.h>

#include "ExtraFunctions.h"

namespace Engine {

    Window::Window()
    {
        m_Display = new SDL_DisplayMode[SDL_GetNumVideoDisplays()];
		m_InputManager = InputManager::getInpuManager();
    }

    Window::~Window()
    {
        delete m_Display;
    }

    SDL_Window* Window::initSystem(int width, int height, int desiredFPS, std::string windowName, unsigned int windowFlags) {

        initSDL();

        if (windowFlags & INVISIBLE) {
            m_WindowFlags |= SDL_WINDOW_HIDDEN;
        }
        if (windowFlags & FULLSCREEN) {
            m_WindowFlags |= SDL_WINDOW_FULLSCREEN;
        }
        if (windowFlags & BORDERLESS) {
            m_WindowFlags |= SDL_WINDOW_BORDERLESS;
        }

        m_SDLWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, m_WindowFlags);

        if (m_SDLWindow == nullptr)
        {
            std::cout << "SDL error: " << SDL_GetError() << std::endl;
            fatalError("Window could not created");
        }

        //getDisplayInfo();

        m_Width = width;
        m_Height = height;
        m_desiredFPS = desiredFPS;

        return m_SDLWindow;
    }

    void Window::quitSystem()
    {
        SDL_DestroyWindow(m_SDLWindow);
        SDL_Quit();
    }

    void Window::calculateFPS()
    {
        static int Timer = SDL_GetTicks();
        static int i = 100;

        int currentTimer = SDL_GetTicks();

        if (Timer != currentTimer) {
            i++;
            // We calculate the FPS of the last 100 frames
            m_detectedFPS[i % 100] = 1000 / (currentTimer - Timer);
            Timer = currentTimer;
        }
    }

	void Window::showFPS()
	{
		static int Timer = SDL_GetTicks();

		int currentTimer = SDL_GetTicks();

		// calculates the average of the last 100 FPS detected every 1 sec
		if (currentTimer - Timer > 1000) {
			Timer = currentTimer;
			int time = 0;
			for (int i = 0; i < (sizeof(m_detectedFPS) / sizeof(*m_detectedFPS)); i++) {
				time += m_detectedFPS[i];
			}
			m_currentFPS = time / 100;
			std::cout << m_currentFPS << std::endl;
		}
	}

	void Window::calculateFrameTime()
	{
		static float Timer = 0;

        float currentTimer = SDL_GetTicks();
        if (Timer != 0) {
            m_frameTime = currentTimer - Timer;
        }
        Timer = currentTimer;      
	}

	void Window::processEvent()
	{
		// Update the map of the keys pressed the previus frame 
		m_InputManager->update();

		SDL_Event SDL_event;
		while (SDL_PollEvent(&SDL_event))
		{
			switch (SDL_event.type) {
			case SDL_QUIT:
				m_GameState = QUIT;
				break;
			case SDL_MOUSEMOTION:
				m_InputManager->setMouseCoords(SDL_event.motion.x, SDL_event.motion.y);
				break;
			case SDL_KEYDOWN:
				m_InputManager->pressKey(SDL_event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				m_InputManager->releaseKey(SDL_event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_InputManager->pressKey(SDL_event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				m_InputManager->releaseKey(SDL_event.button.button);
				break;
			}
		}
	}

    void Window::getDisplayInfo()
    {
        // Get current display mode of all displays.
        for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i) {

            int should_be_zero = SDL_GetCurrentDisplayMode(i, &m_Display[i]);

            if (should_be_zero != 0)
                // In case of error...
                SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
            else {
                // On success, print the current display mode.
                SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, 
                        m_Display[i].w, m_Display[i].h, m_Display[i].refresh_rate);

            }
        }
    }

}