#include "Camera2D.h"
#include <gtc/matrix_transform.hpp>

namespace Engine {

    Camera2D::Camera2D() :
        m_ScreenWidth(500),
        m_ScreenHeight(500),
        m_NeedsMatrixUpdate(true),
        m_Scale(1.0),
        m_Position(0.0f, 0.0f),
        m_CameraMatrix(1.0f),
        m_OrthoMatrix(1.0f)
    {
    }


    Camera2D::~Camera2D()
    {
    }

    void Camera2D::init(float screenWidth, float screeHeight)
    {
        m_ScreenWidth = screenWidth;
        m_ScreenHeight = screeHeight;
        // Creates a matrix for projecting two - dimensional coordinates onto the screen.
        m_OrthoMatrix = glm::ortho(0.0f, m_ScreenWidth, 0.0f, m_ScreenHeight);
    }

    // Updates the camera matrix if needed
    void Camera2D::update()
    {
        if (m_NeedsMatrixUpdate)
        {
            //Camera Translation
            glm::vec3 translate(-m_Position.x + m_ScreenWidth/2, -m_Position.y + m_ScreenHeight/2, 0.0f);
            m_CameraMatrix = glm::translate(m_OrthoMatrix, translate);
            //Camera Scale
            glm::vec3 scale(m_Scale, m_Scale, 0.0f);
            m_CameraMatrix = glm::scale(glm::mat4 (1.0f), scale) * m_CameraMatrix;
            m_NeedsMatrixUpdate = false;
        }
    }

    glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords)
    {
        //Invert y direction
        screenCoords.y = m_ScreenHeight - screenCoords.y;
        //Set the center to zero
        screenCoords -= glm::vec2(m_ScreenWidth / 2, m_ScreenHeight / 2);
        //Scale the coordinates;
        screenCoords /= m_Scale;
        //Translate with the camera position;
        screenCoords += m_Position;
        return screenCoords;
    }

    bool Camera2D::isBoxInView(const glm::vec2& position, const glm::vec2& dimensions) {

        glm::vec2 scaledScreenDimensions = glm::vec2(m_ScreenWidth, m_ScreenHeight)/ m_Scale;
        const float MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;
        const float MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;

        // Center position of the parameters
        glm::vec2 centerPos = position + dimensions / 2.0f;
        // Vector from the input to the camera
        glm::vec2 distVec = centerPos - m_Position;

        float xDepth = MIN_DISTANCE_X - abs(distVec.x);
        float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

        if (xDepth > 0 && yDepth > 0) {
            return true;
        }
        return false;
    }

}


