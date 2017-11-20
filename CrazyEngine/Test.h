#pragma once

class Test {

public:

    static Test* chooseTest(int choice);
    virtual void Init() = 0;
    virtual void draw() = 0;
};
