#pragma once


#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


#include <SDL.h>
#include <glew.h>
#include <glm.hpp>


//! Engine headers
#include "ForwardDeclarations.h"
#include "Enums.h"

#include "Vertex.h"
#include "Texture.h"
#include "2D/Collider2D.h"
#include "2D/Sprite.h"
#include "3D/Mesh.h"

#include "TSingleton.h"
#include "Window.h"
#include "Game.h"
#include "InputManager.h"
#include "ExtraFunctions.h"

#include "GLSLProgram.h"
#include "TextureCache.h"
#include "SpriteBatch.h"

#include "GOmanager.h"
#include "3D/GameObject.h"
#include "2D/GameObject2D.h"
#include "2D/Camera2D.h"
#include "3D/Camera3D.h"


#endif
