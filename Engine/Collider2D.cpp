#include "Collider2D.h"

namespace Engine 
{
    Collider2D::Collider2D(glm::vec2 position, glm::vec2 size) :
        m_Position (position),
        m_Size (size)
    {    
        m_ColliderRadious = (float)m_Size.x / 2;
    }

    Collider2D::~Collider2D()
    {
    }

    Collider2D::Collider2D(const Collider2D & copy)
    {
        m_Position = copy.m_Position;
        m_Size = copy.m_Size;
        m_ColliderRadious = copy.m_ColliderRadious;
    }

    bool Collider2D::checkCircleCollision(const Collider2D & collider)
    {
        const float MIN_DISTANCE = m_ColliderRadious + collider.getColliderRadius();
        glm::vec2 distanceColliders = m_Position - collider.getPosition();
        float powDistance = pow(distanceColliders.x, 2) + pow(distanceColliders.y, 2);
        float powMinDistance = pow(MIN_DISTANCE, 2);

        if (powDistance - powMinDistance < 0)
        {
            return true;
        }

        return false;
    }

    bool Collider2D::checkCircleCollision(const Collider2D& collider, glm::vec2 &depth)
    {
        const float MIN_DISTANCE = m_ColliderRadious + collider.getColliderRadius();
        glm::vec2 distanceColliders = m_Position - collider.getPosition();
        float powDistance = pow(distanceColliders.x, 2) + pow(distanceColliders.y, 2);
        float powMinDistance = pow(MIN_DISTANCE, 2);

        if (powDistance - powMinDistance < 0)
        {
            if (abs(distanceColliders.x) > abs(distanceColliders.y))
            {
                if (distanceColliders.x < 0) {
                    depth.x -= MIN_DISTANCE + distanceColliders.x;
                }
                else
                {
                    depth.x += MIN_DISTANCE - distanceColliders.x;
                }
            }
            else {
                if (distanceColliders.y < 0)
                {
                    depth.y -= MIN_DISTANCE + distanceColliders.y;
                }
                else
                {
                    depth.y += MIN_DISTANCE - distanceColliders.y;
                }
            }
            return true;
        }
        return false;
    }

    bool Collider2D::checkBoxCollision(const Collider2D &collider, glm::vec2 &depth)
    {
        // The minimum distanceColliders before a collision occurs
        const float MIN_DISTANCE_X = m_Size.x / 2.0f  + collider.getSize().x / 2.0f;
        const float MIN_DISTANCE_Y = m_Size.y / 2.0f + collider.getSize().y / 2.0f;
        glm::vec2 centerPosA = m_Position + m_Size / 2.0f;
        glm::vec2 centerPosB = collider.getPosition() + collider.getSize() / 2.0f;
        glm::vec2 distanceColliders = centerPosA - centerPosB;

        // Get the depth of the collision   
        float xDepth = MIN_DISTANCE_X - abs(distanceColliders.x);
        float yDepth = MIN_DISTANCE_Y - abs(distanceColliders.y);

        // If either the depths are > 0, then we collided
        if (xDepth > 0 && yDepth > 0) {
            // Check which collision depth is less
            if ( xDepth < yDepth ) {
                // X collision depth is smaller so we push in X direction
                if (distanceColliders.x < 0) {
                    depth.x -= xDepth;
                }
                else {
                    depth.x += xDepth;
                }
            }
            else {
                // Y collision depth is smaller so we push in Y direction
                if (distanceColliders.y < 0) {
                    depth.y -= yDepth;
                }
                else {
                    depth.y += yDepth;
                }
            }
            return true;
        }
        return false;
    }
}


