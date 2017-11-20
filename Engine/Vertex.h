#pragma once

#include <glew.h>

struct Color {
    int r;
    int g;
    int b;

    Color() : r(1), g(1), b(1) {}
};

struct UV {
    float x;
    float y;
};

struct Vertex {
    float x;
    float y;

    Color color;

    UV uv;
};

struct Vertex3D {
	float x;
	float y;
	float z;

	Color color;

	UV uv;
};
