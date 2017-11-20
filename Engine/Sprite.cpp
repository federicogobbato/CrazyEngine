#include "Sprite.h"

#include "Vertex.h"
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>
#include <SOIL.h>


Sprite::Sprite(Texture* texture, float x, float y, float width, float height) : m_VBO(0), m_VAO(0), m_EBO(0), m_SecondTexture(nullptr)
{
    // Bottom-left
    m_Square[0].x = x;
    m_Square[0].y = y;
    m_Square[0].uv.x = 0;
    m_Square[0].uv.y = 1;

    // Bottom-right
    m_Square[1].x = x + width;
    m_Square[1].y = y;
    m_Square[1].uv.x = 1;
    m_Square[1].uv.y = 1;

    // Top-left
    m_Square[2].x = x;
    m_Square[2].y = y + height;
    m_Square[2].uv.x = 0;
    m_Square[2].uv.y = 0;

    // Top-right
    m_Square[3].x = x + width;
    m_Square[3].y = y + height;
    m_Square[3].uv.x = 1;
    m_Square[3].uv.y = 0;

    m_Texture = texture;
}


Sprite::~Sprite()
{
}

void Sprite::Init(Engine::GLSLProgram* shaderProgram)
{
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

    // Now we can copy the vertex data to m_VBO
    // GL_STATIC_DRAW: The vertex data will be uploaded once and drawn many times(e.g.the world).
    // GL_DYNAMIC_DRAW : The vertex data will be changed from time to time, but drawn many times more than that.
    // GL_STREAM_DRAW : The vertex data will change almost every time it's drawn (e.g. user interface).
    // This usage value will determine in what kind of memory the data is stored on your graphics card for the highest efficiency.
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_Square), m_Square, GL_STATIC_DRAW);

    if (m_EBO == 0) {
        glGenBuffers(1, &m_EBO);
    }

    // Create an element array
    // An element array is filled with unsigned integers referring to vertices bound to GL_ARRAY_BUFFER.
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 1
    };

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    GLuint vertPos = shaderProgram->getAttrLocation("vertexPosition");
    GLuint vertCol = shaderProgram->getAttrLocation("Colors");
    GLuint textCord = shaderProgram->getAttrLocation("texCoord");

    //The vertex attribute array needs to be enabled.
    glEnableVertexAttribArray(vertPos);
    glEnableVertexAttribArray(vertCol);
    glEnableVertexAttribArray(textCord);

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
    glVertexAttribPointer(vertCol, 3, GL_INT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color) );
    glVertexAttribPointer(textCord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv) );

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Sprite::draw(Engine::GLSLProgram* shaderProgram, float time )
{
    glBindVertexArray(m_VAO);

    if (m_SecondTexture != nullptr) {
        alternateSprites(shaderProgram, time);
    }
    else {
        glBindTexture(GL_TEXTURE_2D, m_Texture->getID());
    }

    // Draw a rectangle from the 2 triangles using 6 indices
    // The first parameter is the same as with glDrawArrays, but the other ones all refer to the element buffer.
    // The second parameter specifies the number of indices to draw, 
    // the third parameter specifies the type of the element data and the last parameter specifies the offset.
    // The only real difference is that you're talking about indices instead of vertices now.
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Sprite::alternateSprites(Engine::GLSLProgram* shaderProgram, float time)
{
    GLuint weight = shaderProgram->getUniformLocation("weight");
    glUniform1f(weight, time);

    // The function glActiveTexture specifies which texture unit a texture object is bound to when glBindTexture is called.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Texture->getID());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    // The texture units of the samplers are set using the glUniform
    glUniform1i(shaderProgram->getUniformLocation("tex1"), 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_SecondTexture->getID());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glUniform1i(shaderProgram->getUniformLocation("tex2"), 1);
}





