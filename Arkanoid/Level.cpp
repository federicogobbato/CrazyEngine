#include "Level.h"

#include <iostream>
#include <fstream>

#include <Engine\ExtraFunctions.h>
#include <Engine\Game.h>
#include "Arkanoid.h"

Level::Level() :
    m_BackGroud(nullptr),
    m_Player(nullptr),
    m_Ball(nullptr),
    m_PlayerSpeed(10.0f),
    m_BallSpeed(8.0f),
    m_DeathZone(0.0f),
    m_PlayerStartPosition(0.0f),
    m_BallStartPosition(0.0f),
    m_SizeElement(0.0f),
    m_LevelState(PAUSE_LEVEL)
{
}

Level::~Level()
{
    delete m_BackGroud;

    for (int i = 0; i < m_FrameElements.size(); i++) {
        delete m_FrameElements[i];
    }
    for (int i = 0; i < m_Bricks.size(); i++) {
        delete m_Bricks[i];
    }

    delete m_Player;
    delete m_Ball;
}

// Load the map (a txt file) on a string
void Level::loadLevelMap(const std::string &levelPath, const int & screenWidth, const int &screenHeight)
{
    std::ifstream file(levelPath);
    if (file.fail()) {
        Engine::fatalError("Failed to open " + levelPath);
    }

    std::string line;
    int numLines = 0;

    while (std::getline(file, line))
    {
        m_LevelMap.push_back(line);
        numLines++;
    }
    file.close();

    m_SizeElement.x = float(screenWidth) / m_LevelMap[0].size();
    m_SizeElement.y = float(screenHeight) / numLines;
}

// Create every elements of the level
void Level::loadLevelElements(const int & screenWidth, const int &screenHeight)
{
    m_BackGroud = new Engine::GameObject2D(glm::vec2(-screenWidth / 2, -screenHeight / 2), 0, "Textures/pyramid.png",
                                            Engine::fileExtension::PNG,
                                            glm::vec2(screenWidth, screenHeight));

    glm::vec2 positionNextElement;
    positionNextElement.x = float(-screenWidth) / 2.0f;
    positionNextElement.y = float(screenHeight) / 2.0f - m_SizeElement.y;

    for (int line = 0; line < m_LevelMap.size(); line++)
    {
        for (int column = 0; column < m_LevelMap[line].size(); column++)
        {
            char element = m_LevelMap[line][column];

            switch (element) {
            case 'B':
                createBrick(positionNextElement);
                positionNextElement.x += m_SizeElement.x;
                column++;
                break;
            case 'F':
                createFrame(positionNextElement);
                break;
            case 'P':
                float movementPlayerLimit = screenWidth / 2 - m_SizeElement.x;
                createPlayer(positionNextElement, movementPlayerLimit);
                break;
            }
            positionNextElement.x += m_SizeElement.x;
        }
        positionNextElement.x = float (-screenWidth) / 2;
        positionNextElement.y -= float (m_SizeElement.y);
    }

    m_DeathZone -= (float(screenHeight) / 2.0f) - m_FrameElements[0]->getSize().y;

    for (int i = 0; i < m_Bricks.size(); i++)
    {
        m_BricksInGame.push_back(*m_Bricks[i]);
    }

    // We draw the background just one time
    m_BackGroundSpriteBatch.init();
    m_BackGroundSpriteBatch.begin();
    m_BackGroud->draw(m_BackGroundSpriteBatch);
    for (int i = 0; i < m_FrameElements.size(); i++) {
        m_FrameElements[i]->draw(m_BackGroundSpriteBatch);
    }
    m_BackGroundSpriteBatch.end();

    m_BricksSpriteBatch.init();
    m_BricksSpriteBatch.begin();
    for (int i = 0; i < m_BricksInGame.size(); i++)
    {
        m_BricksInGame[i].draw(m_BricksSpriteBatch);
    }
    m_BricksSpriteBatch.end();
}



void Level::updateLevel(float deltaTime)
{    
    switch (m_LevelState) {
        case PAUSE_LEVEL:
            if (m_Player->update(deltaTime))
            {
                m_LevelState = PLAY_LEVEL;
                m_Ball->update(deltaTime);
                checkBallCollision();
            }
            break;
        case PLAY_LEVEL:
            m_Player->update(deltaTime);
            m_Ball->update(deltaTime);
            checkBallCollision();
            break;
        case GAME_OVER:
            reloadLevel();
            m_LevelState = PAUSE_LEVEL;
            break;
        case WINNER:
            m_LevelState = PAUSE_LEVEL;
            Engine::WindowOPENGL::GetSingleton()->setGameState(Engine::GameState::NEXT_LEVEL);
            break;
    }
}

void Level::drawLevel(Engine::SpriteBatch &spriteBatch)
{
    m_BackGroundSpriteBatch.renderBatch();
    m_BricksSpriteBatch.renderBatch();
    m_Player->draw(spriteBatch);
    m_Ball->draw(spriteBatch);
}


void Level::reloadLevel()
{
    m_Player->setPosition(m_PlayerStartPosition);
    m_Ball->setPosition(m_BallStartPosition);

    m_BricksInGame.clear();
    for (int i = 0; i < m_Bricks.size(); i++)
    {
        m_BricksInGame.push_back(*m_Bricks[i]);
    }

    m_BricksSpriteBatch.begin();
    for (int i = 0; i < m_BricksInGame.size(); i++)
    {
        m_BricksInGame[i].draw(m_BricksSpriteBatch);
    }
    m_BricksSpriteBatch.end();
}


void Level::checkBallCollision()
{   
    Engine::Collider2D *ballCollider = &m_Ball->getCollider();

    glm::vec2 collisionPlayerDepth(0.0f, 0.0f);
    if (ballCollider->checkBoxCollision(m_Player->getCollider(), collisionPlayerDepth)) {
        m_Ball->moveOut(collisionPlayerDepth);
    }

    for (int i = 0; i < m_FrameElements.size(); i++) {    
        glm::vec2 collisionDepth(0.0f, 0.0f);
        if (ballCollider->checkBoxCollision(m_FrameElements[i]->getCollider(), collisionDepth)) {
            if (m_Ball->getPosition().y < m_DeathZone) 
            {
                m_LevelState = GAME_OVER;
                return;
            }
            m_Ball->moveOut(collisionDepth);
            i = m_FrameElements.size();
        }
    }

    for (int i = 0; i < m_BricksInGame.size(); i++) {
        glm::vec2 collisionDepth(0.0f, 0.0f);
        if (ballCollider->checkBoxCollision(m_BricksInGame[i].getCollider(), collisionDepth)) {
            m_Ball->moveOut(collisionDepth);
            m_BricksInGame[i] = m_BricksInGame.back();
            m_BricksInGame.pop_back();
            i--;
            if (m_BricksInGame.size() == 0) {
                m_LevelState = WINNER;
                return;
            }
            else {
                // Every time there is a collision we draw again the bricks
                m_BricksSpriteBatch.begin();
                for (int i = 0; i < m_BricksInGame.size(); i++)
                {
                    m_BricksInGame[i].draw(m_BricksSpriteBatch);
                }
                m_BricksSpriteBatch.end();
            }            
        }
    }
    
}


void Level::createFrame(glm::vec2 position)
{
    ActorGame *newFrameElement = new ActorGame(position, 0, "Textures/element_grey_square.png", 
                                                Engine::fileExtension::PNG, m_SizeElement);
    m_FrameElements.push_back(newFrameElement);
}

void Level::createBrick(glm::vec2 position)
{
    ActorGame *newBrickElement = new ActorGame(position, 0, "Textures/element_blue_rectangle.png", 
                                                Engine::fileExtension::PNG,
                                                glm::vec2(m_SizeElement.x * 2.0f, m_SizeElement.y) );
    m_Bricks.push_back(newBrickElement);
}

void Level::createPlayer(glm::vec2 position, float movementPlayerLimit)
{
    m_PlayerStartPosition = position;
    m_Player = new PlayerArk(m_PlayerStartPosition, 0, "Textures/paddleRed.png", 
                            Engine::fileExtension::PNG,
                            glm::vec2(m_SizeElement.x * 3.0f, m_SizeElement.y / 3.0f),
                            m_PlayerSpeed, movementPlayerLimit);
    m_BallStartPosition = glm::vec2(position.x + m_Player->getSize().x / 2.0f, position.y + m_Player->getSize().y);
    createBall(m_BallStartPosition);
}

void Level::createBall(glm::vec2 position)
{
    m_Ball = new Ball(position, 0, "Textures/ballGrey.png", Engine::fileExtension::PNG, m_SizeElement / 2.0f, m_BallSpeed);
}
