#pragma once

#include "Test.h"
#include <Engine\GLSLProgram.h>
#include <Engine\Camera3D.h>
#include <Engine\Mesh.h>
#include <Engine\TextureCache.h>
#include <Engine\GameObject.h>
#include <Engine\Window.h>
#include <Engine\Cube.h>

class MeshTest : public Test
{
    Engine::GLSLProgram* m_ShaderProgram;
    Camera3D* m_Camera;
	GameObject* m_GameObject;
	Cube* m_Cube;

public:
    MeshTest();
    ~MeshTest();

    virtual void Init();
    virtual void draw();

    void CompileShaders();

    void updateUniformVariables();
};

