#pragma once

#include <SDL.h>
#include <iostream>
#include <ctime>
#include <map>

#include <Engine\Window.h>
#include <Engine\GLSLProgram.h>
#include <Engine\Camera2D.h>
#include <Engine\SpriteBatch.h>
#include <Engine\Vertex.h>
#include <Engine\GameObject2D.h>

#include "Level.h"

class Arkanoid
{
public:
    Arkanoid();
    ~Arkanoid();

    void run();

    void gameLoop();

private:

    void initSystem();

    void initShaders();

    void loadLevel(const std::string &levelPath, int levelNumber);

    void drawGame();

    void setUniformShaderVariables();

    int m_FPS;
    int m_CurrentLevelNumber;
    int m_MaxLevelNumber;

    Engine::GLSLProgram m_TextureProgram; // The shader program
    Engine::SpriteBatch m_ActorsSpriteBatch; // Draws the Actors that need to be updated every frame
    Engine::Camera2D m_Camera; // Main Camera

    std::map<int, Level*> m_Levels;
    Level *m_CurrentLevel;
};

