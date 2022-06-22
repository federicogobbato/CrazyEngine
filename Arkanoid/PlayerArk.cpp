#include "PlayerArk.h"

#include "Level.h"

PlayerArk::PlayerArk(glm::vec2 position, int depth, 
                    const std::string texturePath, Engine::fileExtension fileFormat,
                    glm::vec2 size, float speed, float movementLimit) :
    ActorGame(position, depth, texturePath, fileFormat, size),
    m_Speed (speed),
    m_MovementLimit (movementLimit)
{
}

PlayerArk::~PlayerArk()
{
}

bool PlayerArk::update(const float &deltaTime)
{
    if (Engine::InputManager::getInpuManager()->isKeyDown(SDLK_a)) {
        if (m_Position.x > (- m_MovementLimit)) {
            move(glm::vec2(-1.0f, 0.0f), deltaTime);
        }         
        return true;
    }
    if (Engine::InputManager::getInpuManager()->isKeyDown(SDLK_d)) {
        if (m_Position.x < (m_MovementLimit - m_Size.x)) {
            move(glm::vec2(1.0f, 0.0f), deltaTime);
        } 
        return true;
    }
    return false;
}

void PlayerArk::move(glm::vec2 &direction, const float &deltaTime)
{
    m_Position += direction * m_Speed * deltaTime;
    m_Collider.setPosition(m_Position);
}
