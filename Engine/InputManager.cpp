#include "InputManager.h"

InputManager* InputManager::m_InputeManager = nullptr;

InputManager::InputManager() : m_MouseCoords(0.0f)
{
}

InputManager* InputManager::getInpuManager()
{
	if (m_InputeManager == nullptr) {
		m_InputeManager = new InputManager;
	}
	return m_InputeManager;
}

InputManager::~InputManager()
{
	delete m_InputeManager;
}

void InputManager::update()
{
	for (auto &it : m_KeyMap) {
		m_PreviousKeyMap[it.first] = it.second;
	}
}

void InputManager::pressKey(unsigned int keyID)
{
	m_KeyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID)
{
	m_KeyMap[keyID] = false;
}

void InputManager::setMouseCoords(float x, float y)
{
	m_MouseCoords.x = x;
	m_MouseCoords.y = y;
}

bool InputManager::isKeyDown(unsigned int keyID)
{
	auto it = m_KeyMap.find(keyID);

	if (it != m_KeyMap.end())
	{
		return it->second;
	}
	return false;
}

bool InputManager::isKeyPressed(unsigned int keyID)
{
	if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false) {
		return true;
	}
	return false;
}

bool InputManager::wasKeyDown(unsigned int keyID)
{
	auto it = m_PreviousKeyMap.find(keyID);

	if (it != m_PreviousKeyMap.end())
	{
		return it->second;
	}
	return false;
}





