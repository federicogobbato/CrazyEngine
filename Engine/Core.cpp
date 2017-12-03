#pragma once

#include "Core.h"

#include <iostream>
#include <fstream>


namespace Engine {

    //  tell SDL that we want a forward compatible OpenGL 3.2 context:
    void setOpenGL() {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        // A stencil buffer is an extra buffer, in addition to the color buffer and depth buffer
        // It used to limit the area of the rendering 
    }

    void initSDL()
    {
        // Initialize SDL
        SDL_Init(SDL_INIT_EVERYTHING);

        // Tell SDL that we want a double buffered window so we don't get any flickering 
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    }

}