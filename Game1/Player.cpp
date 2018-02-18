#include "Player.h"

#include <SDL.h>
#include <Engine\InputManager.h>
#include <Engine\WindowOPENGL.h>

using namespace Engine;

void Player::inputCheck()
{
	if (InputManager::getInpuManager()->isKeyDown(SDLK_a)) {
		GameObject::move(glm::vec3(-1.0f, 0.0f, 0.0f) * Engine::WindowOPENGL::GetSingleton()->getFixedDeltaTime() * 0.01f);
		if (GameObject::getTempRotation().z < 20) {
			GameObject::setTempRotation(glm::vec3(0.0f, 0.0f, 1.0f), 90.0f * Engine::WindowOPENGL::GetSingleton()->getFixedDeltaTime() * 0.01f);
		}
	}
	else {
		if (InputManager::getInpuManager()->isKeyDown(SDLK_d)) {
			GameObject::move(glm::vec3(1.0f, 0.0f, 0.0f) * Engine::WindowOPENGL::GetSingleton()->getFixedDeltaTime() * 0.01f);
			if (GameObject::getTempRotation().z > -20) {
				GameObject::setTempRotation(glm::vec3(0.0f, 0.0f, 1.0f), -90.0f * Engine::WindowOPENGL::GetSingleton()->getFixedDeltaTime() * 0.01f);
			}		
		}
		else {
			GameObject::resetTempRotation();
		}
	}

	if (InputManager::getInpuManager()->isKeyPressed(SDL_BUTTON_LEFT)) {
		Engine::PoolObject<GameObject>* bullet = m_Bullets.getElement();
		if (bullet != nullptr) {
			bullet->getElement()->activateGameObject(true);
			bullet->getElement()->setPosition(GameObject::getPosition());
			m_ActiveBullets.push_back(bullet);
		}
	}
}


Player::Player(Mesh* mesh) : GameObject(mesh)
{
}

Player::~Player()
{
	delete m_Cube;
	for each (auto var in m_Bullets.getElements())
	{
		delete var->getElement();
	}
}

void Player::init(Engine::GLSLProgram* shader, int nBullets)
{	
	GameObject::setPosition(glm::vec3(0.0, 0.0, 0.2));
	GameObject::setScale(glm::vec3(0.01f, 0.01f, 0.01f));
	GameObject::setRotation(glm::vec3(0.0f, 1.0f, 0.0f), -90);
	
	m_Cube = new Cube(TextureCache::getTextureCache()->getTexture("textures/ronnie.jpg", fileExtension::JPG));
	m_Cube->Init(shader);

	for (int i = 0; i < nBullets; i++) {
		GameObject* newBullet = new GameObject(m_Cube);
		newBullet->setScale(glm::vec3(0.01f, 0.01f, 0.01f));
		newBullet->setRotation(GameObject::getRotation());
		newBullet->activateGameObject(false);
		m_Bullets.addElement(newBullet);
	}
}

void Player::update()
{
	inputCheck();
	updateBullets();
}

void Player::updateBullets()
{
	for (int i =0 ; i < m_ActiveBullets.size(); i++)
	{
		m_ActiveBullets[i]->getElement()->move(glm::vec3(0.0f, 0.0f, -1.0f) 
												* Engine::WindowOPENGL::GetSingleton()->getFixedDeltaTime() * 0.05f );
		glm::vec3 position = m_ActiveBullets[i]->getElement()->getPosition();
		if (position.z <= -6)
		{
			m_ActiveBullets[i]->getElement()->activateGameObject(false);
			m_Bullets.returnElement(m_ActiveBullets[i]);
			m_ActiveBullets[i] = m_ActiveBullets.back();
			m_ActiveBullets.pop_back();
		}
	}
}

bool Player::checkBulletsCollision(GameObject* gameObject)
{
	for (int i = 0; i < m_ActiveBullets.size(); i++)
	{
		if (m_ActiveBullets[i]->getElement()->checkCollision(gameObject))
		{
			destroyBullet(i);
			return true;
		}
	}
	return false;
}

void Player::destroyBullet(int i) {
	m_ActiveBullets[i]->getElement()->activateGameObject(false);
	m_Bullets.returnElement(m_ActiveBullets[i]);
	m_ActiveBullets[i] = m_ActiveBullets.back();
	m_ActiveBullets.pop_back();
}

