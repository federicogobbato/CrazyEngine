#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "GLSLProgram.h"
#include "Cube.h"

#include <glm.hpp>
 
enum GameObjectState {
	CUBE, MESH
};

class GameObject
{

protected:

	Mesh* m_Mesh;

	Cube* m_Cube;

	glm::mat4 m_ModelMatrix;
	glm::mat4 m_TranslationMatrix;
	glm::mat4 m_RotationMatrix;
	glm::mat4 m_ScaleMatrix;
	glm::mat4 m_TempRotationMatrix;

	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
	glm::vec3 m_TempRotation;

	bool m_ModelMatrixNeedUpdate;
	bool m_State;

	glm::vec3 m_MaxColliderSize;

	int m_ID;

public:

	void setPosition(glm::vec3 position);
	void move(glm::vec3 position);
	void setRotation(glm::vec3 rotation);
	void setRotation(glm::vec3 axis, float rotation);
	void setScale(glm::vec3 scale);

	void setTempRotation(glm::vec3 axis, float rotation);

	glm::vec3 getPosition() {
		return m_Position;
	}

	glm::mat4 getRotationMatrix() {
		return m_RotationMatrix;
	}

	glm::vec3 getRotation() {
		glm::vec4 rotation = glm::vec4(m_Rotation, 0.0f) * glm::inverse(m_RotationMatrix);
		return glm::vec3((int)rotation.x % 360, (int)rotation.y % 360, (int)rotation.z % 360);
	}

	glm::vec3 getTempRotation() {
		return glm::vec3((int)m_TempRotation.x % 360, (int)m_TempRotation.y % 360, (int)m_TempRotation.z % 360);
	}

	glm::vec3 getScale() {
		return m_Scale;
	}

	void resetTempRotation() {
		if (m_TempRotation != glm::vec3()) {
			m_TempRotation = glm::vec3();
			m_TempRotationMatrix = glm::mat4();
			m_ModelMatrixNeedUpdate = true;
		}
	}

	void activateGameObject(bool state) {
		m_State = state;
	}

	bool getState() {
		return m_State;
	}

	glm::vec3 getColliderSize() {
		return m_MaxColliderSize;
	}

	void newModelMatrix() {
		m_ModelMatrixNeedUpdate = true;
	}

	void setID(int id) {
		m_ID = id;
	}

	int getID() {
		return m_ID;
	}

	glm::mat4 updateModelMatrix();

	void draw(Engine::GLSLProgram* shader);

	bool checkCollision(GameObject* object);

	GameObject(Mesh * mesh);
	GameObject(Cube * cube);
	~GameObject();
};

