#pragma once

#include "CoreMinimal.h"

namespace Engine {

    struct Position2D
    {
        float x;
        float y;
    };

    struct ColorRGBA8
    {
        ColorRGBA8() : r(0), g(0), b(0), a(0) {}
        ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) :
            r(R), g(G), b(B), a(A) {}

        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;

        static ColorRGBA8 defaultColor()
        {
            ColorRGBA8 color;
            color.r = 255;
            color.g = 255;
            color.b = 255;
            color.a = 255;
            return color;
        }
    };

    struct UV {
        float x;
        float y;
    };

    struct Vertex 
    {
        Position2D position;
        ColorRGBA8 color;
        UV uv;

        void setPosition(float x, float y)
        {
            position.x = x;
            position.y = y;
        }

        void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
        {
            color.r = r;
            color.g = g;
            color.b = b;
            color.a = a;
        }

        void setUV(float x, float y)
        {
            uv.x = x;
            uv.y = y;
        }
    };

    struct Vertex3D 
    {
        glm::vec3 pos;
        glm::vec3 norm;
        glm::vec2 uv;
    };

    struct Triangle {
        int i, j, k;

        Triangle() : i(0), j(0), k(0) {};
        Triangle(int _i, int _j, int _k) :i(_i), j(_j), k(_k) {}
    };
}
