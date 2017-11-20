#pragma once

#include <Engine\GameObject2D.h>
#include <Engine\Collider2D.h>

class ActorGame : public Engine::GameObject2D

{
public:
    ActorGame(glm::vec2 position, int depth, const std::string texturePath, Engine::fileExtension fileFormat, glm::vec2 size);
    ~ActorGame();

    ActorGame(const ActorGame &copy);

    //getters
    Engine::Collider2D& getCollider() {
        return m_Collider;
    }

protected: 

    Engine::Collider2D m_Collider;
};

