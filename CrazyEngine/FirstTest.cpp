#include "FirstTest.h"
#include <Engine\Vertex.h>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>

void FirstTest::CompileShaders()
{
    m_ShaderProgram->compileShaders("Shaders/Test1.vert", "Shaders/Test1.frag");
    // Its not necessary
    //m_ShaderProgram->addAttribute("vertexPosition");
    //m_ShaderProgram->addAttribute("vertexColor");
    m_ShaderProgram->linkShader();
}



FirstTest::FirstTest() : m_VBO(0) , m_VAO(0)
{
    m_Square[0].x = 0.0;
    m_Square[0].y = 0.5;
    m_Square[0].color.r = 1;
    m_Square[1].x = 0.5;
    m_Square[1].y = -0.5;
    m_Square[1].color.g = 1;
    m_Square[2].x = -0.5;
    m_Square[2].y = -0.5;
    m_Square[2].color.b = 1;
    m_ShaderProgram = new Engine::GLSLProgram;
}


FirstTest::~FirstTest()
{
}

void FirstTest::Init()
{
    CompileShaders();

    if (m_VAO == 0) {
        glGenVertexArrays(1, &m_VAO);
    }

    glBindVertexArray(m_VAO);

    if (m_VBO == 0) {
        // We need a Vertec Buffer Object to upload the vertex data to the graphics card
        glGenBuffers(1, &m_VBO); //Generate 1 buffer 
    }

    // To upload the actual data we need yo make m_VBO the active object
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    GLuint vertPos = m_ShaderProgram->getAttrLocation("vertexPosition");
    GLuint vertCol = m_ShaderProgram->getAttrLocation("vertexColor");

    //The vertex attribute array needs to be enabled.
    glEnableVertexAttribArray(vertPos);
    glEnableVertexAttribArray(vertCol);

    // Now we can specify how the data for that input is retrieved from the array
    //The first parameter references the input.
    //The second parameter specifies the number of values for that input, which is the same as the number of components of the vec.
    //The third parameter specifies the type of each component and the fourth parameter specifies whether the input values should be normalized between - 1.0 and 1.0 (or 0.0 and 1.0 depending on the format) if they aren't floating point numbers.
    //The last two parameters are arguably the most important here as they specify how the attribute is laid out in the vertex array.
    //The first number specifies the stride, or how many bytes are between each position attribute in the array.
    //The value 0 means that there is no data in between.This is currently the case as the position of each vertex is immediately followed by the position of the next vertex.
    //The last parameter specifies the offset, or how many bytes from the start of the array the attribute occurs.
    //Since there are no other attributes, this is 0 as well.
    glVertexAttribPointer(vertPos, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(vertCol, 3, GL_INT, GL_FALSE, sizeof(Vertex), (void*)(2* sizeof(float)));

    // Now we can copy the vertex data to m_VBO
    // GL_STATIC_DRAW: The vertex data will be uploaded once and drawn many times(e.g.the world).
    // GL_DYNAMIC_DRAW : The vertex data will be changed from time to time, but drawn many times more than that.
    // GL_STREAM_DRAW : The vertex data will change almost every time it's drawn (e.g. user interface).
    // This usage value will determine in what kind of memory the data is stored on your graphics card for the highest efficiency.
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_Square), m_Square, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void FirstTest::draw()
{
    static time_t timer;

    m_ShaderProgram->use();
    glBindVertexArray(m_VAO);

    GLint shaderTime = m_ShaderProgram->getUniformLocation("time");
    // The values of uniform variables are changed with any of the glUniformXY functions, 
    // where X is the number of components and Y is the type.Common types are f(float), d(double) and i(integer).
    glUniform1f(shaderTime, (sin(time(&timer)) + 1.0) / 2.0f);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glBindVertexArray(0);
}

