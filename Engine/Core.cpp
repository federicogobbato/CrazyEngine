#pragma once

#include "Core.h"

#include <iostream>
#include <fstream>


bool fileExist(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (file.fail()) {
        std::cout << "Failed to open " + filePath << std::endl;
        return false;
    }
    else {
        return true;
    }
}