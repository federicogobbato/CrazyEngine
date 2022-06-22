#pragma once

#include "CoreMinimal.h"

namespace Engine {

    class Camera2D
    {
    public:
        Camera2D();
        ~Camera2D();

        void init(float screenWidth, float screeHeight);

        void update();

        glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

        bool isBoxInView(const glm::vec2& position, const glm::vec2& dimensions);

        //setter
        void setPosition(const glm::vec2& newPosition) { m_Position = newPosition; m_NeedsMatrixUpdate = true; }
        void setScale(float newScale) { m_Scale = newScale; m_NeedsMatrixUpdate = true; }
        //getter
        glm::vec2 getPosition() { return m_Position; }
        float getScreenWidth() { return m_ScreenWidth; }
        float getScreenHeight() { return m_ScreenHeight; }

        float getScale() { return m_Scale; }
        glm::mat4 getCameraMatrix() { return m_CameraMatrix; }

    private:
        float m_ScreenWidth;
        float m_ScreenHeight;
        bool m_NeedsMatrixUpdate;
        float m_Scale;
        glm::vec2 m_Position;
        glm::mat4 m_CameraMatrix;
        glm::mat4 m_OrthoMatrix;
    };

}


