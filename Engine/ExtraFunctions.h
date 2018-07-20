#pragma once

#include "Window.h"
#include "Game.h"
#include "Texture.h" 

#include <string>
#include <vector>

namespace Engine {

    extern void fatalError(std::string errorString);

    extern bool fileExist(const std::string& dirName_in);

    extern bool readFileToBuffer(const std::string filePath, std::vector<unsigned char> &buffer);

    //extern float calculateFPS(float prevTicks);
}
