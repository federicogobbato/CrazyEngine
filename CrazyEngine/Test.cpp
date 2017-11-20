
#include "Test.h"
#include "FirstTest.h"
#include "SecondTest.h"
#include "SpriteTest.h"
#include "CameraTest.h"
#include "MeshTest.h"

Test* Test::chooseTest(int choice)
{
    switch (choice) {
    case 1:
        return new FirstTest;
        break;
    case 2:
        return new SecondTest;
        break;
    case 3:
        return new SpriteTest;
        break;
    case 4:
        return new CameraTest;
        break;
    case 5:
        return new MeshTest;
        break;
    }

    return nullptr;
}