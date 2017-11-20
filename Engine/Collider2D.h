#pragma once

#include <glm.hpp>

namespace Engine {

    class Collider2D
    {
    public:
        Collider2D(glm::vec2 position, glm::vec2 size);
        ~Collider2D();

        Collider2D(const Collider2D &copy);

        bool checkCircleCollision(const Collider2D& collider);

        bool checkCircleCollision(const Collider2D& collider, glm::vec2 &depth);

        bool checkBoxCollision(const Collider2D& collider, glm::vec2 &depth);

        //setters
        void setPosition(const glm::vec2 &position) {
            m_Position = position;
        }

        //getters
        const glm::vec2& getPosition() const {
            return m_Position;
        }
        const glm::vec2& getSize() const {
            return m_Size;
        }
        const float& getColliderRadius() const {
            return m_ColliderRadious;
        }

    private: 

        glm::vec2 m_Position;
        glm::vec2 m_Size;
        float m_ColliderRadious;
    };

}



