#pragma once

#include <ctime>
#include <Engine\CoreMinimal.h>
#include <Engine\WindowOPENGL.h>

#include "Level.h"

class Arkanoid : public Engine::Game
{
public:

    Arkanoid();
    virtual ~Arkanoid() override;

    void init() override;
    void update() override;
    void quitGame() override;

private:

    void initShaders();
    void setUniformShaderVariables();
    void loadLevel(const std::string &levelPath, int levelNumber);

    void render() override;

    int m_CurrentLevelNumber;
    int m_MaxLevelNumber;

    Engine::WindowOPENGL* m_Window;
    Engine::GLSLProgram m_TextureProgram; // The shader program
    Engine::SpriteBatch m_ActorsSpriteBatch; // Draws the Actors that need to be updated every frame
    Engine::Camera2D m_Camera; // Main Camera

    std::map<int, Level*> m_Levels;
    Level* m_CurrentLevel;
};

