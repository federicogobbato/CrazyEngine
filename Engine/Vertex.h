#pragma once

#include <glew.h>

namespace Engine {

    struct Color {
        int r;
        int g;
        int b;

        Color() : r(1), g(1), b(1) {}
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
    };

    static ColorRGBA8 defaultColor()
    {
        ColorRGBA8 color;
        color.r = 255;
        color.g = 255;
        color.b = 255;
        color.a = 255;
        return color;
    }

    struct UV {
        float x;
        float y;
    };

    struct Position
    {
        float x;
        float y;
    };

    struct Vertex {

        Position position;
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

    struct Vertex3D {
        float x;
        float y;
        float z;

        Color color;

        UV uv;
    };

}
