#pragma once 

#include "Test.h"
#include <iostream>
#include <glew.h>
#include <glm.hpp>
#include <Engine\GLSLProgram.h>
#include <Engine\Vertex.h>


class FirstTest : public Test
{
    GLuint m_VBO; //Vertex Buffer Object
    GLuint m_VAO; //Vertex Array Object
    Engine::GLSLProgram* m_ShaderProgram;
    Vertex m_Square[3];

    void CompileShaders();

public:

    FirstTest();
    ~FirstTest();

    virtual void Init();

    virtual void draw();
};

