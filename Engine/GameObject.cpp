#include "GameObject.h"

#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtc/type_ptr.hpp>

#include "GOmanager.h"

GameObject::GameObject(Mesh* mesh) :
	m_ModelMatrixNeedUpdate(false),
	m_State(true),
	m_Scale(1.0, 1.0, 1.0)
{
	m_Mesh = mesh;
	m_MaxColliderSize = m_Mesh->getMaxSize();
	m_ID = GOmanager::getManager()->addGameObject(this);
}

GameObject::GameObject(Cube* cube) :
	m_ModelMatrixNeedUpdate(false),
	m_State(true),
	m_Scale(1.0, 1.0, 1.0)
{
	m_Cube = cube;
	m_MaxColliderSize = m_Cube->getMaxSize();
	m_ID = GOmanager::getManager()->addGameObject(this);
}

void GameObject::draw(Engine::GLSLProgram* shader)
{
	if (m_Mesh != nullptr) {
		m_Mesh->drawMesh();
	}
	else {
		m_Cube->draw();
	}
}

GameObject::~GameObject()
{
}

glm::mat4 GameObject::updateModelMatrix()
{
	if (m_ModelMatrixNeedUpdate) {

		if (m_TempRotation != glm::vec3()) {
			m_ModelMatrix = m_TranslationMatrix * m_TempRotationMatrix * m_RotationMatrix * m_ScaleMatrix;
		}
		else
		{
			m_ModelMatrix = m_TranslationMatrix * m_RotationMatrix * m_ScaleMatrix;
		}
		m_ModelMatrixNeedUpdate = false;
	}	
	return m_ModelMatrix;
}

void GameObject::setPosition(glm::vec3 position)
{	
	m_Position = position;
	m_TranslationMatrix = glm::translate(glm::mat4(), position);
	m_ModelMatrixNeedUpdate = true;
}

void GameObject::move(glm::vec3 position)
{
	m_Position += position;
	m_TranslationMatrix = glm::translate(m_TranslationMatrix, position);
	m_ModelMatrixNeedUpdate = true;
}

void GameObject::setRotation(glm::vec3 rotation)
{
	m_Rotation = rotation;
	m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(rotation.x), 
						glm::vec3(1.0, 0.0, 0.0));
	m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(rotation.y),
						glm::vec3(0.0, 1.0, 0.0));
	m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(rotation.z),
						glm::vec3(0.0, 0.0, 1.0));
	m_ModelMatrixNeedUpdate = true;
}

void GameObject::setRotation(glm::vec3 axis, float rotation)
{
	m_Rotation += axis * rotation;
	m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(rotation), axis);
	m_ModelMatrixNeedUpdate = true;
}

void GameObject::setScale(glm::vec3 scale)
{
	m_Scale *= scale;
	m_ScaleMatrix = glm::scale(m_ScaleMatrix, scale);
	m_ModelMatrixNeedUpdate = true;
	m_MaxColliderSize *= scale;
}

void GameObject::setTempRotation(glm::vec3 axis, float rotation)
{
	m_TempRotation += axis * rotation;
	m_TempRotationMatrix = glm::rotate(m_TempRotationMatrix, glm::radians(rotation), axis);
	m_ModelMatrixNeedUpdate = true;
}

bool GameObject::checkCollision(GameObject * object)
{
	glm::vec3 distanceObjects = m_Position - object->getPosition();
	float MIN_DISTANCE_X = m_MaxColliderSize.x + object->getColliderSize().x;
	float MIN_DISTANCE_Y = m_MaxColliderSize.y + object->getColliderSize().y;
	float MIN_DISTANCE_Z = m_MaxColliderSize.z + object->getColliderSize().z;

	float xDepth = MIN_DISTANCE_X - abs(distanceObjects.x);
	float yDepth = MIN_DISTANCE_Y - abs(distanceObjects.y);
	float zDepth = MIN_DISTANCE_Z - abs(distanceObjects.z);

	if (xDepth > 0.0f && yDepth > 0.0f && zDepth > 0.0f) {
		return true;
	}

	return false;
}