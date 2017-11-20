#pragma once

#include "Test.h"

#include <Engine\TextureCache.h>
#include <Engine\GLSLProgram.h>
#include <Engine\Sprite.h>
#include <Engine\Camera3D.h>

class CameraTest : public Test
{
    Engine::GLSLProgram* m_ShaderProgram;
    Sprite* m_Sprite;
    Camera3D* m_Camera;

public:
    CameraTest();
    ~CameraTest();

    virtual void Init();
    virtual void draw();

    void CompileShaders();
    void updateUniformVariables(float time = 1.0f);
};

