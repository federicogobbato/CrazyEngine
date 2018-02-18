#pragma once

#include <SDL.h>

#include "Window.h"

namespace Engine {

    class WindowSDL : public Window
    {
        SDL_Renderer* m_Renderer;

    public:

        SDL_Window* initSystem(int width, int height, int desiredFPS, std::string windowName, unsigned int windowFlags) override;
        void quitSystem() override;

        void clearRenderer() override;
        void swapBuffer() override;

        void setVSync() override {};
        void disableVSync() override {};

        SDL_Renderer* getRenderer() const  {
            return m_Renderer;
        };

        WindowSDL();
        ~WindowSDL();
    };

}




