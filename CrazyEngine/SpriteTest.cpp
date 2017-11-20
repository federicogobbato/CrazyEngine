#include "SpriteTest.h"

#include <Engine\Window.h>


SpriteTest::SpriteTest()
{
    m_ShaderProgram = new Engine::GLSLProgram;
}


SpriteTest::~SpriteTest()
{
}

void SpriteTest::Init()
{
    CompileShaders();    
    m_Sprite = new Sprite(TextureCache::getTextureCache()->getTexture("textures/ronnie.jpg"));
    m_Sprite->setSecondTexture(TextureCache::getTextureCache()->getTexture("textures/kristina.jpg"));
    m_Sprite->Init(m_ShaderProgram);
}

void SpriteTest::draw()
{
    static float time = 0;

    int refreshRate = Engine::Window::getWindow()->getMonitoRefreshRate();
    time++;
    if (time > refreshRate) {
        time = 0;
    }

    m_ShaderProgram->use();
    m_Sprite->draw(m_ShaderProgram, time / refreshRate);
}

void SpriteTest::CompileShaders()
{
    m_ShaderProgram->compileShaders("Shaders/Texture.vert", "Shaders/Texture.frag");
    //m_ShaderProgram->addAttribute("vertexPosition");
    //m_ShaderProgram->addAttribute("vertexColor");
    //m_ShaderProgram->addAttribute("texCoord");
    m_ShaderProgram->linkShader();
}