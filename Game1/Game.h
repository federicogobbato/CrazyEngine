#pragma once

#include <Engine\GLSLProgram.h>
#include <Engine\Camera3D.h>
#include <Engine\Mesh.h>
#include <Engine\TextureCache.h>
#include <Engine\Window.h>
#include <Engine\Cube.h>
#include <Engine\Pool.h>

#include "Player.h"

class Game
{
	Engine::GLSLProgram* m_CameraShader;
	Camera3D* m_Camera;
	Player* m_Player;

	Mesh* m_SpaceShipMesh;
	Engine::Pool<GameObject> m_Enemies;
	std::vector<Engine::PoolObject<GameObject>*> m_ActiveEnemies;

	glm::vec3 m_EnemyStartPosition[3];

	int m_Difficulty;

	int m_nDestroyedEnemies;
	bool m_PlayerDetroyed;

	void draw();
	void CompileShaders();
	void updateUniformVariables();

	void checkCollision();

	void updateEnemies();

	void destroyEnemy(int);

public:
	Game(int difficulty = 2);
	~Game();

	void init();

	void update();
};

