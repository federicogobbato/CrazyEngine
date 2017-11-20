#include "Game.h"

#include <ctime>
#include <gtc/type_ptr.hpp>
#include <gtc/random.hpp>

#include <Engine\GOmanager.h>

Game::Game(int difficulty) : m_EnemyStartPosition{ glm::vec3(0.0f, 0.0f, -6.0f), 
									glm::vec3(-0.6f, 0.0f, -6.0f), 
									glm::vec3(0.6f, 0.0f, -6.0f) }, 
									m_nDestroyedEnemies(0),
									m_PlayerDetroyed(false),
									m_Difficulty(difficulty)
{
	m_CameraShader = new Engine::GLSLProgram;
	m_Camera = new Camera3D(glm::vec3(0.0, 0.5, 1.0), 800, 600);	
	m_SpaceShipMesh = new Mesh(TextureCache::getTextureCache()->getTexture("textures/dark_fighter_color.pbm", PBM));	
}


Game::~Game()
{
	delete m_CameraShader;
	delete m_Camera;
	delete m_SpaceShipMesh;
	delete m_Player;
	for each (auto var in m_Enemies.getElements())
	{
		delete var->getElement();
	}
}

void Game::init()
{
	srand(time(0));

	CompileShaders();

	if (m_SpaceShipMesh->loadMesh("meshes/dark_fighter_6.obj")) {
		m_SpaceShipMesh->loadGPUMesh(m_CameraShader);
	}

	m_Player = new Player(m_SpaceShipMesh);
	m_Player->init(m_CameraShader, 5);

	for (int i = 0; i < 30; i++) {
		GameObject* enemy = new GameObject(m_SpaceShipMesh);
		enemy->setScale(glm::vec3(0.01f, 0.01f, 0.01f));
		enemy->setRotation(glm::vec3(0.0f, 1.0f, 0.0f), 90);
		enemy->activateGameObject(false);
		m_Enemies.addElement(enemy);
	}
}

void Game::update()
{
	static int timerAtBegin = SDL_GetTicks();
	static int timerPrevSecond = timerAtBegin;

	int currentTime = SDL_GetTicks();

	if (currentTime - timerAtBegin < 30000 && !m_PlayerDetroyed)
	{
		int physicStep = 0;

		// Every frame we update the position and check the collisions "MaxPhysicSteps" times
		while (physicStep < Engine::Window::getWindow()->getMaxPhysicSteps())
		{
			m_Player->update();

			updateEnemies();

			checkCollision();

			// Update the Input Manager to build the map of the keys pressed the first physic step 
			if (physicStep == 0) {
				InputManager::getInpuManager()->update();
			}

			physicStep++;
		}

		if (currentTime - timerPrevSecond > 1000) {
			std::cout << "Time: " << currentTime / 1000 << std::endl;
			std::cout << "Destroyed Enemy Ships: " << m_nDestroyedEnemies << std::endl << std::endl;
			timerPrevSecond = currentTime;
		}
	}

	draw();
}

void Game::updateEnemies()
{
	static int timePrevSpawn = SDL_GetTicks();

	int timer = SDL_GetTicks();

	// Every 2 seconds we activate 1-3 new enemies 
	if (timer - timePrevSpawn > 2000) {
		int i = 0;
		while (i < 3) {
			int prob = glm::linearRand(0, m_Difficulty);
			std::cout << prob << std::endl;
			if (prob) {
				Engine::PoolObject<GameObject>* enemy = m_Enemies.getElement();
				if (enemy != nullptr) {
					enemy->getElement()->activateGameObject(true);
					enemy->getElement()->setPosition(m_EnemyStartPosition[i]);
					m_ActiveEnemies.push_back(enemy);
				}
			}
			i++;
		}
		timePrevSpawn = timer;
	}

	for (int i=0; i < m_ActiveEnemies.size() ; i++)
	{
		m_ActiveEnemies[i]->getElement()->move(glm::vec3(0.0, 0.0, 1.0) 
												* Engine::Window::getWindow()->getPhysicDeltaTime());
		if (m_ActiveEnemies[i]->getElement()->getPosition().z > 1.0f) {
			std::cout << "Main ship destroyed" << std::endl;
			std::cout << "GAME OVER!!!!" << std::endl;
			m_PlayerDetroyed = true;
		}
	}
}

void Game::draw()
{
	m_CameraShader->use();
	m_Camera->update();
	updateUniformVariables();
	GOmanager::getManager()->drawGameObjects(m_CameraShader);
}

void Game::CompileShaders()
{
	m_CameraShader->compileShaders("Shaders/MeshCamera3D.vert", "Shaders/MeshCamera3D.frag");
	m_CameraShader->linkShader();
}

void Game::updateUniformVariables()
{
	GLint uniCamMatrix = m_CameraShader->getUniformLocation("cameraMatrix");
	if (uniCamMatrix != GL_INVALID_INDEX) {
		// The second parameter of the glUniformMatrix4fv function specifies how many matrices are to be uploaded, 
		// because you can have arrays of matrices in GLSL.
		// The third parameter specifies whether the specified matrix should be transposed before usage.
		// The last parameter specifies the matrix to upload, 
		// where the glm::value_ptr function converts the matrix class into an array of 16 (4x4) floats.
		glUniformMatrix4fv(uniCamMatrix, 1, GL_FALSE, glm::value_ptr(m_Camera->getCameraMatrix()));
	}
}

void Game::checkCollision()
{
	for (int i = 0; i < m_ActiveEnemies.size(); i++)
	{
		if (m_Player->checkCollision(m_ActiveEnemies[i]->getElement())) {
			std::cout << "GAME OVER!!!!" << std::endl;
			m_PlayerDetroyed = true;
		}

		if (m_Player->checkBulletsCollision(m_ActiveEnemies[i]->getElement())) {
			destroyEnemy(i);
			m_nDestroyedEnemies++;
		}
	}
}

void Game::destroyEnemy(int i)
{
	m_ActiveEnemies[i]->getElement()->activateGameObject(false);
	m_Enemies.returnElement(m_ActiveEnemies[i]);
	m_ActiveEnemies[i] = m_ActiveEnemies.back();
	m_ActiveEnemies.pop_back();
}
