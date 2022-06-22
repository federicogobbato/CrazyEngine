#pragma once

#include "CoreMinimal.h"

namespace Engine {

    extern void fatalError(std::string errorString);

    extern bool fileExist(const std::string& dirName_in);

    extern bool readFileToBuffer(const std::string filePath, std::vector<unsigned char> &buffer);

    //extern float startCalculateFPS(float prevTicks);
}
