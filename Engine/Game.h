#pragma once

#include "TSingleton.h"

namespace Engine {

    class Game 
    {
        virtual void render() = 0;

    public:

        virtual void init() = 0;

        virtual void update() = 0;

    };

}




