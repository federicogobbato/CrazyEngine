#pragma once

#include <string>
#include <vector>
#include <glm.hpp>


#include <Engine\SpriteBatch.h>
#include <Engine\InputManager.h>
#include <Engine\Collider2D.h>

#include "ActorGame.h"
#include "PlayerArk.h"
#include "Ball.h"


enum LevelState {
    PAUSE_LEVEL,
    PLAY_LEVEL,
    GAME_OVER,
    WINNER,
};

class Level
{
public:
    Level();
    ~Level();

    void loadLevelMap(const std::string &levelPath, const int &screenWidth, const int &screenHeight);

    void loadLevelElements(const int & screenWidth, const int &screenHeight);

    void reloadLevel();

    void updateLevel(float deltaTime);

    void drawLevel(Engine::SpriteBatch &spriteBatch);

private:

    void checkBallCollision();

    void createFrame(glm::vec2 position);
    void createBrick(glm::vec2 position);
    void createPlayer(glm::vec2 position, float movementPlayerLimit);
    void createBall(glm::vec2 position);

    Engine::SpriteBatch m_BackGroundSpriteBatch; // Draws the background
    Engine::SpriteBatch m_BricksSpriteBatch;    // Draws the Bricks

    std::vector<std::string> m_LevelMap;
    Engine::GameObject2D *m_BackGroud;
    std::vector<ActorGame*> m_FrameElements;
    std::vector<ActorGame> m_BricksInGame;  // Bricks updated at runtime
    std::vector<ActorGame*> m_Bricks;       // Sample Bricks   
    
    PlayerArk* m_Player;
    Ball* m_Ball;

    float m_PlayerSpeed;
    float m_BallSpeed;

    glm::vec2 m_PlayerStartPosition;
    glm::vec2 m_BallStartPosition;
    glm::vec2 m_SizeElement;
    float m_DeathZone;

    LevelState m_LevelState;    
};

