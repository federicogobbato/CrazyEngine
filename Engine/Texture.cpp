#include "Texture.h"

#include "picoPNG.h"
////#include <SOIL.h>

namespace Engine {

    Texture::Texture() : m_ID(0), m_Width(0), m_Height(0)
    {
    }

    Texture::~Texture()
    {
    }

    void Texture::loadData(const std::string& texturePath) {

        // (We don't draw a texture. We map or apply a texture on a primitive)
        // Generate the OpenGL texture object
        glGenTextures(1, &m_ID);
        // Bind the texture object
        glBindTexture(GL_TEXTURE_2D, m_ID);

        loadTexture(texturePath);

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

    void TextureJPG::loadTexture(const std::string & texturePath)
    {
        fatalError("jpg not supported at the moment");
    }

    void TexturePNG::loadTexture(const std::string& texturePath) {

        //This is the input data to decodePNG, which we load from a file
        std::vector<unsigned char> in;
        //This is the output data from decodePNG, which is the pixel data for our texture
        std::vector<unsigned char> out;

        unsigned long width, height;
        // Read in the image file contents into a Buffer
        if (!readFileToBuffer(texturePath, in)) {
            fatalError("Failed to load PNG file to buffer!");
        }

        // Decode the .png format into an array of pixels
        int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
        if (errorCode != 0) {
            fatalError("dedodePNG failed with error: " + std::to_string(errorCode));
        }

        // UPLOAD the image data (pixels) to the texture.
        // The arguments describe the parameters of the texture image, such as height, width, width of the border, 
        // level-of-detail number (see glTexParameter), and number of color components provided. 
        // The last three arguments describe how the image is represented in memory. 
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

        m_Width = width;
        m_Height = height;
    }

    struct Texel {
        char r, g, b, a;
    };

    void TexturePBM::loadTexture(const std::string & texturePath)
    {
        std::vector<Texel> CPUtexture;

        std::ifstream infile(texturePath, std::ios::binary);

        int depth;
        std::string token;
        infile >> token >> m_Width >> m_Height >> depth;

        for (int i = 0; i < m_Width*m_Height; i++) {
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
}