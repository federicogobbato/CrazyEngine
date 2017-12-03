#pragma once

#include "Game.h"
#include "Texture.h" 

#include <string>
#include <vector>

namespace Engine {

    template <class T>
    void fatalError(std::string errorString, T* game)
    {
        std::cout << errorString << std::endl;
        system("PAUSE");
        delete game;
        Window::GetSingleton()->quitSystem();
        exit(1);
    }

    extern void fatalError(std::string errorString);

    extern bool fileExist(const std::string& dirName_in);

    extern bool readFileToBuffer(const std::string filePath, std::vector<unsigned char> &buffer);

    //extern float calculateFPS(float prevTicks);
}
