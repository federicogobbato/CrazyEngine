#pragma once

#include <glm.hpp>

#include "GLSLProgram.h"

class Camera3D
{
    glm::vec3 m_Position;
	glm::vec3 m_LookAt;
    float m_ScreenWidth;
    float m_ScreenHeight;
    bool m_NeedUpdate;
	float m_Scale;
	glm::vec3 m_UPaxis;
	glm::vec3 m_XCameraAxis;
	glm::vec3 m_YCameraAxis;
	glm::vec3 m_ZCameraAxis;

    glm::mat4 m_CameraMatrix;

public:
    
    void setPosition(glm::vec3 position) {
        m_Position += position;
        m_NeedUpdate = true;
    }

	void setScale(int scale) {
		m_Scale = scale;
		m_NeedUpdate = true;
	}

	void setPointToLook(glm::vec3 lookAt) {
		m_LookAt = lookAt;
		m_NeedUpdate;
	}

	void setZAxis(glm::vec3 upAxis) {
		m_UPaxis = upAxis;
		m_NeedUpdate = true;
	}

    const glm::mat4& getCameraMatrix() const {
        return m_CameraMatrix;
    }
    
    Camera3D(glm::vec3 position, float screenWidth, float screenHeight);
    ~Camera3D();

    void update();

};

