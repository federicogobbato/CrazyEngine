#pragma once

#include <string>
#include <glew.h>

namespace Engine {

    class Texture
    {
    protected:
        GLuint m_ID;
        int m_Width;
        int m_Height;

        virtual void loadTexture(const std::string& texturePath) = 0;
    public:

        GLuint getID() const {
            return m_ID;
        }

        Texture();
        ~Texture();

        void loadData(const std::string& texturePath);
    };


    class TexturePNG : public Texture {
        virtual void loadTexture(const std::string& texturePath);
    };

    class TexturePBM : public Texture {
        virtual void loadTexture(const std::string& texturePath);
    };

    class TextureJPG : public Texture {
        virtual void loadTexture(const std::string& texturePath);
    };

}