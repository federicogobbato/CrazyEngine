#include "Texture.h"

#include <vector>
#include <SOIL.h>
#include <fstream>


Texture::Texture() : m_ID(0), m_Width(0), m_Height(0)
{

}

Texture::~Texture()
{
}

void Texture::loadData(const std::string& texturePath, fileExtension flag) {

    // Generate the OpenGL texture object
    glGenTextures(1, &m_ID);
    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, m_ID);

	switch (flag)
	{
	case JPG:
		loadJPGTexture(texturePath);
		break;
	case PBM:
		loadPGMTexture(texturePath);
		break;
	default:
		break;
	}

    // Set some texture parameters
    // (Set how the texture is sampled when the UV size coordinates are outside the range of 0 to 1) 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // (Set the filtering)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Generate the mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0); 
}


void Texture::loadPGMTexture(const std::string & texturePath)
{
    std::vector<Texel> CPUtexture;

    std::ifstream infile(texturePath, std::ios::binary);

    int depth;
    std::string token;
    infile >> token >> m_Width >> m_Height >> depth;

    for (int i = 0; i<m_Width*m_Height; i++) {
        char rgb[4];
        infile.read(rgb, 4);
        Texel t;
        t.r = rgb[0];
        t.g = rgb[1];
        t.b = rgb[2];
        t.a = rgb[3];
        CPUtexture.push_back(t);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, &CPUtexture[0]);
}

void Texture::loadJPGTexture(const std::string & texturePath)
{
	unsigned char* image = SOIL_load_image(&texturePath[0], &m_Width, &m_Height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
}
