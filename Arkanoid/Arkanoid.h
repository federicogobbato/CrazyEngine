#pragma once

#include <SDL.h>
#include <iostream>
#include <ctime>
#include <map>

#include <Engine\TSingleton.h>
#include <Engine\WindowOPENGL.h>
#include <Engine\Game.h>
#include <Engine\GLSLProgram.h>
#include <Engine\Camera2D.h>
#include <Engine\SpriteBatch.h>
#include <Engine\Vertex.h>
#include <Engine\GameObject2D.h>

#include "Level.h"

class Arkanoid : public Engine::Game, public Engine::TSingleton<Arkanoid>
{
public:

    Arkanoid();
    ~Arkanoid();

    void init() override;

    void update() override;

private:

    void initShaders();

    void loadLevel(const std::string &levelPath, int levelNumber);

    void render() override;

    void setUniformShaderVariables();

    int m_CurrentLevelNumber;
    int m_MaxLevelNumber;

    Engine::WindowOPENGL* m_Window;
    Engine::GLSLProgram m_TextureProgram; // The shader program
    Engine::SpriteBatch m_ActorsSpriteBatch; // Draws the Actors that need to be updated every frame
    Engine::Camera2D m_Camera; // Main Camera

    std::map<int, Level*> m_Levels;
    Level* m_CurrentLevel;
};

