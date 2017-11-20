#pragma once

#include <Engine\InputManager.h>

#include "ActorGame.h"


class PlayerArk : public ActorGame
{
public:
    PlayerArk(glm::vec2 position, int depth, const std::string texturePath, Engine::fileExtension fileFormat, glm::vec2 size,
                float speed, float movementLimit);
    ~PlayerArk();

    bool update(const float &deltaTime);

private:

    void move(glm::vec2 &direction, const float &deltaTime);

    float m_Speed;
    float m_MovementLimit;

};

