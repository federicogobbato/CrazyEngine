#pragma once

#include "CoreMinimal.h"

namespace Engine {

    class WindowOPENGL : public Window
    {
        SDL_GLContext m_GLContext;

        /* Tell SDL that we want a forward compatible OpenGL 3.2 context */
        void setOpenGL();

    public:

        /* Create an OpenGL context, set buffer,  and initialize glew */
        SDL_Window* initSystem(int width, int height, int desiredFPS, std::string windowName, unsigned int windowFlags) override;

        virtual ~WindowOPENGL() override;

        /* Clear the color and depth buffer */
        void clearRenderer() override;

        /* Swap our buffer and draw everything to the sreen */
        void swapBuffer() override;

        void setVSync() override {
            if (m_GLContext)
                SDL_GL_SetSwapInterval(1); // enabled      
        }

        void disableVSync() override {
            if (m_GLContext)
                SDL_GL_SetSwapInterval(0); // disabled
        }
    };

}



