#pragma once

#include "Test.h"
#include <Engine\TextureCache.h>
#include <Engine\GLSLProgram.h>
#include <Engine\Sprite.h>


class SpriteTest : public Test
{
    Engine::GLSLProgram* m_ShaderProgram;
    Sprite* m_Sprite;

public:
    SpriteTest();
    ~SpriteTest();

    virtual void Init();
    virtual void draw();

    void CompileShaders();

};

