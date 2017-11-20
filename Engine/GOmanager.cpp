
#include "GOmanager.h"
#include <gtc/type_ptr.hpp>
#include "GameObject.h"

GOmanager* GOmanager::m_GOmanager = nullptr;

GOmanager::GOmanager()
{
}


GOmanager::~GOmanager()
{
	delete m_GOmanager;
}

int GOmanager::addGameObject(GameObject* gameObject)
{
	m_GameObjects.push_back(gameObject);
	m_ModelMatrices.push_back(glm::mat4());
	return m_nGameObjectsCreated++;
}

void GOmanager::removeGameObject(GameObject* gameObject){
	m_GameObjects.back()->setID(gameObject->getID());
	m_GameObjects[gameObject->getID()] = m_GameObjects.back();
	m_GameObjects.pop_back();
	m_ModelMatrices[gameObject->getID()] = m_ModelMatrices.back();
	m_ModelMatrices.pop_back();
	m_nGameObjectsCreated--;
}

void GOmanager::drawGameObjects(Engine::GLSLProgram* shader) {

	// Updates the Model Matrix of every gameobject 
	// and we build the array of matrices to pass to the vertex shader
	for(int i=0 ; i < m_GameObjects.size(); i++)
	{
		m_ModelMatrices[i] = m_GameObjects[i]->updateModelMatrix();
	}
	
	// Pass the array of matrices to the vertex shader
	glUniformMatrix4fv(shader->getUniformLocation("modelMatrix"), m_GameObjects.size(), GL_FALSE, glm::value_ptr(m_ModelMatrices[0]));

	for (int i=0 ; i < m_GameObjects.size(); i++)
	{
		if (m_GameObjects[i]->getState()) {
			// Set the correct matrix to use in the vertex shader
			glUniform1i(shader->getUniformLocation("ID"), i);
			m_GameObjects[i]->draw(shader);
		}
	}
}
