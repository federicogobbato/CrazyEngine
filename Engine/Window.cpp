#include "Window.h"

#include <SDL_image.h>
#include <chrono>

#include "InputManager.h"

namespace Engine {

    Window::~Window()
    {
        SDL_DestroyWindow(m_SDLWindow);
        SDL_Quit();
    }

    void Window::initSDL()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
        {
            std::cout << "SDL error: " << SDL_GetError() << std::endl;
            fatalError("SDL could be inizialized");
        }
    }

    SDL_Window* Window::initSystem(int width, int height, int desiredFPS, std::string windowName, unsigned int windowFlags) 
    {
        initSDL();

        m_Display = new SDL_DisplayMode[SDL_GetNumVideoDisplays()];
        m_InputManager = InputManager::getInpuManager();

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

        getDisplayInfo();

        m_Width = width;
        m_Height = height;
        m_DesiredFPS = desiredFPS;

        return m_SDLWindow;
    }

    void Window::quitSystem()
    {
        SDL_DestroyWindow(m_SDLWindow);
        SDL_Quit();
    }

    void Window::calculateFixedDeltaTime()
    {
        static auto lastTimeFrame = std::chrono::high_resolution_clock::now();
        static const float DESIRED_FRAMETIME = 1000.0f / m_DesiredFPS;

        auto currentTime = std::chrono::high_resolution_clock::now();
        auto timeNano = currentTime - lastTimeFrame;
        ////auto time = std::chrono::duration_cast<std::chrono::milliseconds>(timeNano).count();

        if (time > 0)
        {
            auto frameTime = timeNano.count();
            float currentDeltaTime = (frameTime/1000000.0f) / DESIRED_FRAMETIME;
            m_FixedDeltaTime = currentDeltaTime / m_MaxPhysicSteps;
            lastTimeFrame = currentTime;

            if (m_ShowFPS)
            {
                ++m_FramesDetected;
                m_LastSixtyFrameTime += frameTime;
            }
        }
    }

	void Window::showFPS()
	{ 
		if (m_FramesDetected == 60 && m_LastSixtyFrameTime > 0)
        {   
            double averageFrameTime = m_LastSixtyFrameTime / (60 * 1000000);          
            std::cout << 1000 / averageFrameTime << std::endl;
            m_FramesDetected = 0;
            m_LastSixtyFrameTime = 0;
		}
	}

	bool Window::processEvent()
	{
        if (m_GameState == GameState::QUIT) return false;

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

        return m_GameState != QUIT;
	}

    void Window::getDisplayInfo()
    {
        // Get current display mode of all displays.
        for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i) {

            int should_be_zero = SDL_GetCurrentDisplayMode(i, &m_Display[i]);

            if (should_be_zero != 0)
                SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
            else {
                // On success, print the current display mode.
                SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, 
                        m_Display[i].w, m_Display[i].h, m_Display[i].refresh_rate);

            }
        }
    }

}