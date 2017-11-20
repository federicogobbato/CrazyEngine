#pragma once

#include <glm.hpp>

#include "ActorGame.h"

class Ball : public ActorGame
{
public:
    Ball(glm::vec2 position, int depth, 
            const std::string texturePath,
            Engine::fileExtension fileFormat,
            glm::vec2 size, float speed);

    ~Ball();

    void update(const float &deltaTime);

    void moveOut(glm::vec2 &depth);

private:
    
    float m_Speed;
    glm::vec2 m_Direction;

};

