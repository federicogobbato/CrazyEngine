#include "Window.h"

#include <iostream>


namespace Engine {

	Window* Window::m_Window = nullptr;

    Window::Window() : m_currentFPS(0), m_deltaTime(0), m_maxPhysicSteps(3)
    {
        m_Display = new SDL_DisplayMode[SDL_GetNumVideoDisplays()];
		m_InputManager = InputManager::getInpuManager();
    }

	Window* Window::getWindow()
	{
		if (m_Window == nullptr) {
			m_Window = new Window;
		}
		return m_Window;
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

	void Window::calculateDeltaTime()
	{
		static float Timer = SDL_GetTicks();

		float currentTimer = SDL_GetTicks();
		m_deltaTime = (currentTimer - Timer) / 1000;
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

	Window::~Window()
    {
		delete m_Display;
		delete m_Window;
    }


    SDL_Window* Window::initSystem(int width, int height, int desiredFPS) {

        setOpenGL();

        SDL_Init(SDL_INIT_VIDEO);

        m_SDLWindow = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

        if (m_SDLWindow == nullptr)
        {
            std::cout << "Could not create window, error: " << SDL_GetError() << std::endl;
        }

        // Set up our OpenGL context
        m_glContext = SDL_GL_CreateContext(m_SDLWindow);
        if (m_glContext == nullptr) {
            std::cout << "SDL_GL context could not be created" << std::endl;
        }

        GLenum error = glewInit();
        if (error != GLEW_OK) {
            // Problem: glewInit failed, something is seriously wrong.
            std::cout << "glewInit failed: " << glewGetErrorString(error) << std::endl;
        }

        // Tell SDL that we want a double buffered window so we don't get any flickering 
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        glClearColor(0.0f, 0.0f, 0.0, 1.0f);

        // Set VSync
        SDL_GL_SetSwapInterval(1); // enabled
        //SDL_GL_SetSwapInterval(0); // disabled

        getDisplayInfo();

        //Enable alpha blend
        glEnable(GL_BLEND);
        //Pixels can be drawn using a function that blends 
        //the incoming (source, for example a png image) RGBA values with the RGBA values 
        //that are already in the frame buffer (the destination values, for example the background).
        //glBlendFunc defines the operation of blending for all draw buffers when it is enabled.
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_desiredFPS = desiredFPS;

        return m_SDLWindow;
    }

    void Window::quitSystem()
    {
        SDL_GL_DeleteContext(m_glContext);
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


    //  tell SDL that we want a forward compatible OpenGL 3.2 context:
    void Window::setOpenGL() {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        // A stencil buffer is an extra buffer, in addition to the color buffer and depth buffer
        // It used to limit the area of the rendering 
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