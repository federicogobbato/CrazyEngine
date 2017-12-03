#pragma once

#include <Engine\Game.h>
#include <Engine\Window.h>
#include <Engine\TSingleton.h>

class PathFinding : public Engine::Game, TSingleton<PathFinding>
{
    SDL_Texture* m_Texture; // the new SDL_Texture variable
    SDL_Rect m_SourceRectangle; 
    SDL_Rect m_DestinationRectangle; 

    void loadTexture();

public:
    PathFinding();
    ~PathFinding();

    virtual void init();

    virtual void update();

    void render();

};

