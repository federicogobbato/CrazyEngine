#pragma once

#include <unordered_map>
#include <glm.hpp>


class InputManager
{
public:
	static InputManager* getInpuManager();
	~InputManager();

	void update();

	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);

	void setMouseCoords(float x, float y);
	glm::vec2 getMouseCoords() const { return m_MouseCoords; }

	bool isKeyDown(unsigned int keyID);
	bool isKeyPressed(unsigned int keyID);

private:

	InputManager();
	static InputManager* m_InputeManager;

	bool wasKeyDown(unsigned int keyID);

	std::unordered_map<unsigned int, bool> m_KeyMap;

	std::unordered_map<unsigned int, bool> m_PreviousKeyMap;
	glm::vec2 m_MouseCoords;
};




