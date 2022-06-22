#pragma once

#include "CoreMinimal.h"

namespace Engine {

    class GOmanager
    {
        static GOmanager* m_GOmanager;

        std::vector<GameObject*> m_GameObjects;
        std::vector<glm::mat4> m_ModelMatrices;

        GOmanager();

        int m_nGameObjectsCreated;

    public:
        ~GOmanager();

        static GOmanager* getManager() {
            if (m_GOmanager == nullptr) {
                m_GOmanager = new GOmanager;
            }
            return m_GOmanager;
        }

        int addGameObject(GameObject* gameObject);

        void removeGameObject(GameObject * gameObject);

        void drawGameObjects(GLSLProgram* shader);
    };

}