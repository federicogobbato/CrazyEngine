#include "GameTest1.h"

#include <ctime>
#include <gtc/type_ptr.hpp>
#include <gtc/random.hpp>

#include <Engine\GOmanager.h>

using namespace Engine;

GameTest1::GameTest1(int difficulty) : m_EnemyStartPosition{ glm::vec3(0.0f, 0.0f, -6.0f),
									glm::vec3(-0.6f, 0.0f, -6.0f), 
									glm::vec3(0.6f, 0.0f, -6.0f) }, 
									m_nDestroyedEnemies(0),
									m_PlayerDetroyed(false),
									m_Difficulty(difficulty)
{
    m_Window = static_cast<WindowOPENGL*>(Window::GetSingleton());
	m_CameraShader = new Engine::GLSLProgram;
	m_Camera = new Camera3D(glm::vec3(0.0, 0.5, 1.0), m_Window->getScreenWidth(), m_Window->getScreenHeight());	
	m_SpaceShipMesh = new Mesh(TextureCache::getTextureCache()->getTexture("textures/dark_fighter_color.pbm", PBM));	
}


GameTest1::~GameTest1()
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

void GameTest1::init()
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

void GameTest1::update()
{
	static int timerAtBegin = SDL_GetTicks();
	static int timerPrevSecond = timerAtBegin;

	int currentTime = SDL_GetTicks();

    if (!m_PlayerDetroyed)
	{
		int physicStep = 0;

		// Every frame we update the position and check the collisions "MaxPhysicSteps" times
		while (physicStep < m_Window->getMaxPhysicSteps() && !m_PlayerDetroyed)
		{
			m_Player->update();

			updateEnemies();

			checkCollision();           

			physicStep++;

            m_Window->processEvent();
		}

		if (currentTime - timerPrevSecond > 1000) {
			std::cout << "Time: " << currentTime / 1000 << std::endl;
			std::cout << "Destroyed Enemy Ships: " << m_nDestroyedEnemies << std::endl << std::endl;
			timerPrevSecond = currentTime;
		}
	}

    render();
}

void GameTest1::updateEnemies()
{
	static int timePrevSpawn = SDL_GetTicks();

	int timer = SDL_GetTicks();

	// Every 2 seconds we activate 1-3 new enemies 
	if (timer - timePrevSpawn > 2000) {
		int i = 0;
		while (i < 3) {
			int probabilityNewEnemy = glm::linearRand(0, m_Difficulty);
			//std::cout << probabilityNewEnemy << std::endl;
			if (probabilityNewEnemy) {
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
												* m_Window->getFixedDeltaTime() * 0.01f);
		if (m_ActiveEnemies[i]->getElement()->getPosition().z > 1.0f) {
			std::cout << "Main ship destroyed" << std::endl;
			std::cout << "GAME OVER!!!!" << std::endl;
			m_PlayerDetroyed = true;
            //m_Window->setGameState(GameState::QUIT);
            break;
		}
	}
}

void GameTest1::render()
{
	m_CameraShader->use();
	m_Camera->update();
	updateUniformVariables();
	GOmanager::getManager()->drawGameObjects(m_CameraShader);
}

void GameTest1::CompileShaders()
{
	m_CameraShader->compileShaders("Shaders/MeshCamera3D.vert", "Shaders/MeshCamera3D.frag");
	m_CameraShader->linkShader();
}

void GameTest1::updateUniformVariables()
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

void GameTest1::checkCollision()
{
	for (int i = 0; i < m_ActiveEnemies.size(); i++)
	{
		if (m_Player->checkCollision(m_ActiveEnemies[i]->getElement())) {
            std::cout << "YOU are destroyed" << std::endl;
			std::cout << "GAME OVER!!!!" << std::endl;
			m_PlayerDetroyed = true;
            //m_Window->setGameState(GameState::QUIT);
            break;
		}

		if (m_Player->checkBulletsCollision(m_ActiveEnemies[i]->getElement())) {
			destroyEnemy(i);
			m_nDestroyedEnemies++;
		}
	}
}

void GameTest1::destroyEnemy(int i)
{
	m_ActiveEnemies[i]->getElement()->activateGameObject(false);
	m_Enemies.returnElement(m_ActiveEnemies[i]);
	m_ActiveEnemies[i] = m_ActiveEnemies.back();
	m_ActiveEnemies.pop_back();
}
