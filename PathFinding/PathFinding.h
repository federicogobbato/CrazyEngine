#pragma once

#include <Engine\Game.h>
#include <Engine\WindowSDL.h>


class PathFinding : public Engine::TSingleton<PathFinding>
{
    Engine::WindowSDL* m_Window;

    SDL_Texture* m_Texture; // the new SDL_Texture variable
    SDL_Rect m_SourceRectangle; 
    SDL_Rect m_DestinationRectangle; 

    void loadTexture();

    void render();

public:
    PathFinding();
    ~PathFinding();

    void init();

    void update();

};

