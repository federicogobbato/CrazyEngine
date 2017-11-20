#pragma once

#include "Texture.h" 

#include <string>
#include <vector>

namespace Engine {

    extern int initEngine();

    extern void fatalError(std::string errorString);

    extern bool readFileToBuffer(const std::string filePath, std::vector<unsigned char> &buffer);

    extern float calculateFPS(float prevTicks);
}
