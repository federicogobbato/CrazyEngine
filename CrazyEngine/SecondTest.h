#pragma once 

#include "Test.h"
#include <iostream>
#include <glew.h>
#include <glm.hpp>
#include <Engine\GLSLProgram.h>
#include <Engine\Vertex.h>


class SecondTest : public Test
{
    GLuint m_VBO; //Vertex Buffer Object
    GLuint m_VAO; //Vertex Array Object
    GLuint m_EBO; //Element array
    Engine::GLSLProgram* m_ShaderProgram;
    Vertex m_Square[4];

    void CompileShaders();

public:

    SecondTest();
    ~SecondTest();

    virtual void Init();

    virtual void draw();
};

