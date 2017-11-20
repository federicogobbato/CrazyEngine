#pragma once

#include <string>
#include <glew.h>


enum fileExtension {
	JPG,
	PBM
};

struct Texel {
    char r, g, b, a;
};

class Texture
{
    GLuint m_ID;
    int m_Width;
    int m_Height;

    void loadPGMTexture(const std::string& texturePath);
	void loadJPGTexture(const std::string& texturePath);

public:

    GLuint getID() const {
        return m_ID;
    }

    Texture();
    ~Texture();

    void loadData(const std::string& texturePath, fileExtension flag);
};

