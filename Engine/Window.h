#pragma once

#include <glew.h>
#include <SDL.h>
#include <string>

#include "TSingleton.h"
#include "InputManager.h"

namespace Engine {

    enum WindowFlags {
        INVISIBLE = 0x1,
        FULLSCREEN = 0x2,
        BORDERLESS = 0x4,
    };

    enum SDL_Flags {
        OPENGL_CONTEXT = 0X1,
        SDL_RENDERER = 0X2,
    };

	enum GameState {
		START,
		QUIT,
        PLAY,
        PAUSE,
        NEXT_LEVEL
	};

    class Window : public TSingleton<Window>
    {
        //friend class TSingleton<Window>;
    protected:

        SDL_Window* m_SDLWindow;
        SDL_DisplayMode* m_Display;
		InputManager* m_InputManager;

        unsigned int m_WindowFlags;
        int m_Width;
        int m_Height;
		int m_desiredFPS;
		int m_currentFPS = 0;
		int m_detectedFPS[100];
		float m_frameTime = 0;
		int m_maxPhysicSteps = 3;
        GameState m_GameState = START;

        void getDisplayInfo();

    public:

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

        Window();
        ~Window();

        void initSDL();
        virtual SDL_Window* initSystem(int width= 1280, int height= 720, int desiredFPS= 60, std::string windowName= "test", unsigned int windowFlags = 0);
        virtual void quitSystem();
        void calculateFPS();
        void showFPS();
        void calculateFrameTime();
        bool processEvent();

        virtual void clearRenderer() = 0;
        virtual void swapBuffer() = 0;
        virtual void setVSync() = 0;
        virtual void disableVSync() = 0;
    };
}




