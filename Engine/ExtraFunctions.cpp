
#include "ExtraFunctions.h"

#include <iostream>
#include <fstream>

#include <SDL.h>
#include <glew.h>

#include "Window.h"

namespace Engine {

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

    void fatalError(std::string errorString)
    {
        std::cout << errorString << std::endl;
        system("PAUSE");
        Game::GetSingleton()->quitGame();
        Window::GetSingleton()->quitSystem();
        exit(1);
    }

    bool readFileToBuffer(const std::string filePath, std::vector<unsigned char> &buffer) {

        // Operations are performed in binary mode rather than text
        std::ifstream file(filePath, std::ios::binary);
        if (file.fail())
        {
            perror(filePath.c_str());
            return false;
        }
        // Here, "seekg" is used to move the position to the end of the file
        file.seekg(0, std::ios::end);

        // Get the file size
        // (Returns the position of the current character in the input stream)
        int fileSize = file.tellg();
        // Back to the beginning
        file.seekg(0, std::ios::beg);
        // Reduce the file size by any header bytes that might be present
        fileSize -= file.tellg();

        buffer.resize(fileSize);
        // Extracts "fileSize" characters from the stream and stores them into the buffer
        file.read((char*)&(buffer[0]), fileSize);
        file.close();

        return true;
    }

    //float calculateFPS(float prevTicks)
    //{
    //    static const int NUM_SAMPLES = 10;
    //    static float frameTimes[NUM_SAMPLES];
    //    static int currentFrame = 0;

    //    float currentTicks = SDL_GetTicks();
    //    float frameTime = currentTicks - prevTicks;
    //    prevTicks = currentTicks;
    //    int i = currentFrame % NUM_SAMPLES;
    //    frameTimes[currentFrame % NUM_SAMPLES] = frameTime;
    //    currentFrame++;
    //           
    //    int count;
    //    if (currentFrame < NUM_SAMPLES) {
    //        count = currentFrame;
    //    }
    //    else {
    //        count = NUM_SAMPLES;
    //    }

    //    float frameTimeAverage = 0;
    //    for (int i = 0; i < count; i++) {
    //        frameTimeAverage += frameTimes[i];
    //    }
    //    frameTimeAverage /= count;

    //    if (frameTimeAverage > 0)
    //    {
    //        return 1000.0f / frameTimeAverage;
    //    }
    //    else {
    //        return 0.0f;
    //    }
    //}
}