#pragma once

#include "Vertex.h"
#include "GLSLProgram.h"
#include "Texture.h"
#include <glm.hpp>

class Cube
{
	GLuint m_VBO; //Vertex Buffer Object
	GLuint m_VAO; //Vertex Array Object
	GLuint m_EBO; //Element array
	Vertex3D m_Vertices[12];
	Texture* m_Texture;

	glm::vec3 m_MaxSize;

public:
	Cube(Texture* texture);
	~Cube();
	void Init(Engine::GLSLProgram * shaderProgram, float x = 0.5f, float y = 0.5f, float z = 0.5f);
	void draw();

	glm::vec3 getMaxSize() {
		return m_MaxSize;
	}
};

