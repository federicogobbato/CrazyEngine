#include "Camera3D.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>


Camera3D::Camera3D(glm::vec3 position, float screenWidth, float screenHeight):
    m_Position(position),
	m_LookAt(glm::vec3(0.0f, 0.0f, 0.0f)),
    m_ScreenWidth(screenWidth),
    m_ScreenHeight(screenHeight),
    m_NeedUpdate(true),
    m_CameraMatrix(0),
	m_Scale(1.0f),
	m_UPaxis(glm::vec3(0.0f, 1.0f, 0.0f))	
{
}

Camera3D::~Camera3D()
{
}

void Camera3D::update()
{
    if (m_NeedUpdate) {

		glm::mat4 scale;
		scale = glm::scale(scale, glm::vec3(m_Scale));

        // VIEW MATRIX
        // glm::lookAt simulates a moving camera. 
        // The first parameter specifies the position of the camera, 
        // the second where you want to look at, in world space, and the third the up axis.
        // Here up is defined as the Y axis, which implies that the XZ plane is the "ground".
        glm::mat4 view = glm::lookAt(
            m_Position,
            m_LookAt,
			m_UPaxis
            );

        // PROJECTION MATRIX
        // glm::perspective creates a perspective projection matrix.
        // The first parameter is the vertical field - of - view, 
        // the second parameter the aspect ratio of the screen and the last two parameters are the near and far planes.
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), m_ScreenWidth / m_ScreenHeight, 0.2f, 1000.0f);

        // WE MUST MULTIPLY THE MATRICES BY THE FOLLOWING ORDER
        m_CameraMatrix = proj * view * scale;

        m_NeedUpdate = false;
    }
}

// CAMERA 2D
//glm::vec3 translate(m_ScreenWidth / 2, m_ScreenHeight / 2, 0.0f);
//m_CameraMatrix = glm::ortho(0.0f, m_ScreenWidth, 0.0f, m_ScreenHeight);
//m_CameraMatrix = glm::translate(m_CameraMatrix, translate);
//glm::vec3 scale(3, 3, 0.0f);
//m_CameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_CameraMatrix;