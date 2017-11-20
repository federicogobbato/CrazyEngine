#pragma once

#include <glew.h>
#include <SDL.h>
#include <string>
#include "InputManager.h"

namespace Engine {

    enum WindowFlags {
        INVISIBLE = 0x1,
        FULLSCREEN = 0x2,
        BORDERLESS = 0x4,
    };

	enum GameState {
		START,
		QUIT,
        PLAY,
        PAUSE,
        NEXT_LEVEL
	};

    class Window 
    {
        SDL_Window* m_SDLWindow;
        SDL_GLContext m_GLContext;
        SDL_DisplayMode* m_Display;

		InputManager* m_InputManager;

        int m_Width;
        int m_Height;
		int m_desiredFPS;
		int m_currentFPS;
		int m_detectedFPS[100];
		float m_frameTime;
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

        int getScreenWidth() {
            return m_Width;
        }

        int getScreenHeight() {
            return m_Height;
        }

		GameState getGameState() {
			return m_GameState;
		}

        void setGameState(GameState gameState) {
            m_GameState = gameState;
        }

		float getFixedDeltaTime() {
            const float DESIRED_FRAMETIME = 1000.0f / m_desiredFPS;
            float currentDeltaTime = m_frameTime / DESIRED_FRAMETIME;
			return currentDeltaTime / m_maxPhysicSteps;
		}

		int getMaxPhysicSteps() {
			return m_maxPhysicSteps;
		}     

        ~Window();

        SDL_Window* initSystem(int width= 1280, int height= 720, int desiredFPS= 60, std::string windowName= "test", unsigned int currentFlags = 0);
        void quitSystem();
        void swapBuffer();

		void calculateFPS();
		void showFPS();
		void calculateFrameTime();
		void processEvent();
    };
}




