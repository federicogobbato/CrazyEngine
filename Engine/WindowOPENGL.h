#pragma once

#include <SDL.h>

#include "Window.h"

namespace Engine {

    class WindowOPENGL : public Window
    {
        SDL_GLContext m_GLContext;

    public:

        void setVSync() override {
            if (m_GLContext)
                SDL_GL_SetSwapInterval(1); // enabled      
        }

        void disableVSync() override {
            if (m_GLContext)
                SDL_GL_SetSwapInterval(0); // disabled
        }

        WindowOPENGL();
        ~WindowOPENGL();

        SDL_Window* initSystem(int width, int height, int desiredFPS, std::string windowName, unsigned int windowFlags) override;
        void quitSystem() override;

        void clearRenderer() override;
        void swapBuffer() override;



    };

}



