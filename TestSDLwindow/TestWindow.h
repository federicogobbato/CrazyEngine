#pragma once

#include <Engine\Game.h>
#include <Engine\WindowSDL.h>


class TestWindow : public Engine::TSingleton<TestWindow>
{
    Engine::WindowSDL* m_Window;

    SDL_Texture* m_Texture; // the new SDL_Texture variable
    SDL_Rect m_SourceRectangle; 
    SDL_Rect m_DestinationRectangle; 

    ////void loadTexture();

    void render();

public:
    TestWindow();
    ~TestWindow();

    void init();

    void update();

};

