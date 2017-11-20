#pragma once

#include <Engine\GameObject.h>
#include <Engine\Pool.h>
#include <Engine\Cube.h>

class Player : public GameObject
{
	GameObject* m_Enemy1;

	Cube* m_Cube;
	Engine::Pool<GameObject> m_Bullets;

	std::vector<Engine::PoolObject<GameObject>*> m_ActiveBullets;

	void inputCheck();

	void updateBullets();

	void destroyBullet(int i);

public:
	Player(Mesh* mesh);
	~Player();

	void init(Engine::GLSLProgram* shader, int nBullets);

	void update();

	bool checkBulletsCollision(GameObject* gameObject);

};

