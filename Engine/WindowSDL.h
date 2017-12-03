#pragma once

#include <SDL.h>

#include "Window.h"

namespace Engine {

    class WindowSDL : public Window 
    {
        SDL_Renderer* m_SDLRenderer;

    public:

        SDL_Renderer* getSDLRenderer() const {
            return m_SDLRenderer;
        }

        SDL_Window* initSystem(int width, int height, int desiredFPS, std::string windowName, unsigned int windowFlags) override;
        void quitSystem() override;

        void clearRenderer() override;
        void swapBuffer() override;

        WindowSDL();
        ~WindowSDL();
    };

}




