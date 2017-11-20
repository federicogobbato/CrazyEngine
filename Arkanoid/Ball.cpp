#include "Ball.h"

#include <gtc\random.hpp>
#include <gtx\rotate_vector.hpp>

Ball::Ball(glm::vec2 position, int depth,
    const std::string texturePath, Engine::fileExtension fileFormat,
    glm::vec2 size, float speed) :
    ActorGame(position, depth, texturePath, fileFormat, size),
    m_Speed(speed)
{
    int spin = glm::linearRand(-100, 100);
    m_Direction = glm::vec2(-1.0f * spin, 1.0f * abs(spin));
    m_Direction = glm::normalize(m_Direction);
}


Ball::~Ball()
{
}

void Ball::update(const float &deltaTime)
{
    m_Position += m_Direction * m_Speed * deltaTime;
    m_Collider.setPosition(m_Position);

}

void Ball::moveOut(glm::vec2 &depth)
{
    m_Position += depth;
    m_Collider.setPosition(m_Position);
    if ( abs(depth.x) > abs(depth.y)) 
    {
        m_Direction.x = - m_Direction.x;
    }
    else {
        m_Direction.y = - m_Direction.y;
    }
}



