#pragma once

#include <glew.h>
#include <SDL.h>
#include <string>
#include "InputManager.h"

namespace Engine {

	enum GameState {
		START,
		QUIT,
	};

    class Window 
    {
        SDL_Window* m_SDLWindow;
        SDL_GLContext m_glContext;
        SDL_DisplayMode* m_Display;

		InputManager* m_InputManager;

		int m_desiredFPS;
		int m_currentFPS;
		int m_detectedFPS[100];
		float m_deltaTime;
		int m_maxPhysicSteps;

		GameState m_GameState = START;

        void setOpenGL();
        void getDisplayInfo();

		static Window* m_Window;
		Window();

    public:

		static Window* getWindow();

        SDL_Window* getSDLWindow() const {
            return m_SDLWindow;
        }

        int getMonitoRefreshRate() {
            return m_Display[0].refresh_rate;
        }

		GameState getGameState() {
			return m_GameState;
		}

		float getDeltaTime() {
			return m_deltaTime;
		}

		float getPhysicDeltaTime() {
			return m_deltaTime / m_maxPhysicSteps;
		}

		int getMaxPhysicSteps() {
			return m_maxPhysicSteps;
		}

        ~Window();

        SDL_Window* initSystem(int width= 800, int height= 600, int desiredFPS= 60);
        void quitSystem();

		void calculateFPS();
		void showFPS();
		void calculateDeltaTime();
		void processEvent();
    };
}




