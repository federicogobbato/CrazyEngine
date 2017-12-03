

#include "WindowOPENGL.h"

#include <iostream>

#include "ExtraFunctions.h"

namespace Engine {

    WindowOPENGL::WindowOPENGL()
    {
        m_WindowFlags = SDL_WINDOW_OPENGL;

        setOpenGL();
    }


    WindowOPENGL::~WindowOPENGL()
    {
    }

    SDL_Window * WindowOPENGL::initSystem(int width, int height, int desiredFPS, std::string windowName, unsigned int windowFlags)
    {
        Window::initSystem();

        // Set up our OpenGL context
        m_GLContext = SDL_GL_CreateContext(m_SDLWindow);
        if (m_GLContext == nullptr) {
            fatalError("SDL_GL context could not be created");
        }

        GLenum error = glewInit();
        if (error != GLEW_OK) {
            // Problem: glewInit failed, something is seriously wrong.
            std::cout << "GLEW error: " << glewGetErrorString(error) << std::endl;
            fatalError("glewInit failed !");
        }

        std::cout << "*** OpenGL Version: " << glGetString(GL_VERSION) << " ***" << std::endl;

        // Specify clear values for the color buffers
        // Set the background color to blue
        glClearColor(0.0f, 0.5f, 1.0f, 1.0f);

        //Enable alpha blend
        glEnable(GL_BLEND);
        //Pixels can be drawn using a function that blends 
        //the incoming (source, for example a png image) RGBA values with the RGBA values 
        //that are already in the frame buffer (the destination values, for example the background).
        //glBlendFunc defines the operation of blending for all draw buffers when it is enabled.
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        return m_SDLWindow;
    }

    void WindowOPENGL::quitSystem()
    {
        SDL_GL_DeleteContext(m_GLContext);    

        Window::quitSystem();
    }

    void WindowOPENGL::clearRenderer()
    {
        // Set the base depth to 1.0
        glClearDepth(1.0);
        // Clear the color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void WindowOPENGL::swapBuffer()
    {
        // Swap our buffer and draw everything to the sreen
        // Use this function to update a window with OpenGL rendering (This is used with double-buffered OpenGL contexts, which are the default)
        SDL_GL_SwapWindow(m_SDLWindow);
    }

}


