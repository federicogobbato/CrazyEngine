#include "ActorGame.h"



ActorGame::ActorGame(glm::vec2 position, int depth, const std::string texturePath, Engine::fileExtension fileFormat, glm::vec2 size) :
    GameObject2D(position, depth, texturePath, fileFormat, size),
    m_Collider(position, size)
{

}


ActorGame::~ActorGame()
{
}

ActorGame::ActorGame(const ActorGame & copy) :
    GameObject2D(copy), 
    m_Collider(copy.m_Collider)
{

}
