#include "MeshTest.h"

#include <iostream>
#include <gtc/type_ptr.hpp>
#include <Engine\InputManager.h>

MeshTest::MeshTest()
{
    m_ShaderProgram = new Engine::GLSLProgram;

    m_Camera = new Camera3D(glm::vec3(2.2, 2.2, 2.0), 800, 600);
	m_GameObject = new GameObject(TextureCache::getTextureCache()->getTexture("textures/dark_fighter_color.pbm", PBM));
	
	//m_Cube = new Cube(TextureCache::getTextureCache()->getTexture("textures/ronnie.jpg"));
}


MeshTest::~MeshTest()
{
	delete m_ShaderProgram;
	delete m_Camera;
	delete m_GameObject;
	//delete m_Cube;
}

void MeshTest::Init()
{
    CompileShaders();

	m_GameObject->initMesh(m_ShaderProgram, "meshes/dark_fighter_6.obj");
	m_GameObject->setScale(glm::vec3(0.02f, 0.02f, 0.02f));
	m_GameObject->setRotation(glm::vec3(0.0f, 0.0f, 1.0f), 45);

	//m_Cube->Init(m_ShaderProgram);
}

void MeshTest::draw()
{
	if (InputManager::getInpuManager()->isKeyDown(SDLK_a)) {
		//glm::vec4 newPosition = glm::vec4(1.0,0.0,0.0,0.0) 
		//	* m_GameObject->getRotationMatrix()
		//	* CrazyEngine::Window::getWindow()->getDeltaTime();

		//m_GameObject->setPosition(glm::vec3(newPosition.x, newPosition.y, newPosition.z));

		m_GameObject->setPosition(m_GameObject->getXaxis() * Engine::Window::getWindow()->getDeltaTime() * 10.0f);
	}

	if (InputManager::getInpuManager()->isKeyDown(SDLK_d)) {
		glm::vec4 newPosition = glm::vec4(-1.0, 0.0, 0.0, 0.0)
			* m_GameObject->getRotationMatrix()
			* Engine::Window::getWindow()->getDeltaTime();

		m_GameObject->setPosition(glm::vec3(newPosition.x, newPosition.y, newPosition.z));
	}

    m_ShaderProgram->use();
    m_Camera->update(m_ShaderProgram);
    updateUniformVariables();

	m_GameObject->draw(m_ShaderProgram);

	//m_Cube->draw(m_ShaderProgram);
}


void MeshTest::CompileShaders()
{
    m_ShaderProgram->compileShaders("Shaders/MeshCamera3D.vert", "Shaders/MeshCamera3D.frag");
	//m_ShaderProgram->compileShaders("Shaders/Cube.vert", "Shaders/Cube.frag");
    m_ShaderProgram->linkShader();
}

void MeshTest::updateUniformVariables() {

    GLint uniCamMatrix = m_ShaderProgram->getUniformLocation("cameraMatrix");
    // The second parameter of the glUniformMatrix4fv function specifies how many matrices are to be uploaded, 
    // because you can have arrays of matrices in GLSL.
    // The third parameter specifies whether the specified matrix should be transposed before usage.
    // The last parameter specifies the matrix to upload, 
    // where the glm::value_ptr function converts the matrix class into an array of 16 (4x4) floats.
    glUniformMatrix4fv(uniCamMatrix, 1, GL_FALSE, glm::value_ptr(m_Camera->getCameraMatrix()));
}