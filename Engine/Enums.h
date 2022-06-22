#pragma once

namespace Engine
{
    enum WindowFlags 
    {
        INVISIBLE = 0x1,
        FULLSCREEN = 0x2,
        BORDERLESS = 0x4,
    };

    enum SDL_Flags 
    {
        OPENGL_CONTEXT = 0X1,
        SDL_RENDERER = 0X2,
    };

    enum GameState 
    {
        START,
        QUIT,
        PLAY,
        PAUSE,
        NEXT_LEVEL
    };

    enum fileExtension {
        PNG,
        JPG,
        PBM,
        SDL_IMAGE
    };


}