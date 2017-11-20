#include "CameraTest.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <Engine\Window.h>


CameraTest::CameraTest()
{
    m_ShaderProgram = new Engine::GLSLProgram;
    m_Camera = new Camera3D(glm::vec3(1.2, 1.2, 1.2), 800, 600);
}


CameraTest::~CameraTest()
{
}

void CameraTest::Init()
{
    CompileShaders();
    m_Sprite = new Sprite(TextureCache::getTextureCache()->getTexture("textures/ronnie.jpg"));
    m_Sprite->Init(m_ShaderProgram);
}

void CameraTest::draw()
{
    static float time = 0;

    int refreshRate = Engine::Window::getWindow()->getMonitoRefreshRate();
    time++;
    if (time > refreshRate) {
        time = 0;
    }

    m_ShaderProgram->use();
    m_Camera->update(m_ShaderProgram);
    updateUniformVariables(time / refreshRate);
    m_Sprite->draw(m_ShaderProgram);
}

void CameraTest::CompileShaders()
{
    m_ShaderProgram->compileShaders("Shaders/Camera3D.vert", "Shaders/Camera3D.frag");
    m_ShaderProgram->linkShader();
}

void CameraTest::updateUniformVariables(float time) {

    GLint uniCamMatrix = m_ShaderProgram->getUniformLocation("cameraMatrix");
    // The second parameter of the glUniformMatrix4fv function specifies how many matrices are to be uploaded, 
    // because you can have arrays of matrices in GLSL.
    // The third parameter specifies whether the specified matrix should be transposed before usage.
    // The last parameter specifies the matrix to upload, 
    // where the glm::value_ptr function converts the matrix class into an array of 16 (4x4) floats.
    glUniformMatrix4fv(uniCamMatrix, 1, GL_FALSE, glm::value_ptr(m_Camera->getCameraMatrix()));

    // ROTATE THE SPRITE
    // 4-by-4 matrix, identity matrix by default
    glm::mat4 rotationMatrix;
    // Multiplies this matrix by a rotation transformation of 360 degrees around the Z axis.
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(360.0f) * time, glm::vec3(0.0f, 0.0f, 1.0f));

    GLint uniRotMatrix = m_ShaderProgram->getUniformLocation("rotationMatrix");
    // The second parameter of the glUniformMatrix4fv function specifies how many matrices are to be uploaded, 
    // because you can have arrays of matrices in GLSL.
    // The third parameter specifies whether the specified matrix should be transposed before usage.
    // The last parameter specifies the matrix to upload, 
    // where the glm::value_ptr function converts the matrix class into an array of 16 (4x4) floats.
    glUniformMatrix4fv(uniRotMatrix, 1, GL_FALSE, glm::value_ptr(rotationMatrix));
}
