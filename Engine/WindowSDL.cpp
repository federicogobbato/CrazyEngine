
#include "WindowSDL.h"

#include <iostream>
#include "ExtraFunctions.h"

namespace Engine {

    WindowSDL::WindowSDL()
    {
    }


    WindowSDL::~WindowSDL()
    {
    }

    SDL_Window * WindowSDL::initSystem(int width, int height, int desiredFPS, std::string windowName, unsigned int windowFlags)
    {
        Window::initSystem();

        m_Renderer = SDL_CreateRenderer(m_SDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (m_Renderer == nullptr)
        {
            std::cout << "SDL Error: " << SDL_GetError() << std::endl;
            fatalError("SDL_Renderer could not be created");
        }
        else {
            //Initialize renderer color 
            SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 255);
        }

        return m_SDLWindow;
    }

    void WindowSDL::quitSystem()
    {
        SDL_DestroyRenderer(m_Renderer);
        
        Window::quitSystem();
    }

    void WindowSDL::clearRenderer()
    {
        SDL_RenderClear(m_Renderer); // clear the renderer to the draw color
    }

    void WindowSDL::swapBuffer()
    {
        SDL_RenderPresent(m_Renderer); // draw to the screen
    }

}


