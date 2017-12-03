#pragma once
#include <map>
#include "Texture.h"

namespace Engine {

    enum fileExtension {
        PNG,
        JPG,
        PBM,
        SDL_IMAGE
    };

    class TextureCache
    {
        static TextureCache* m_TextureCache;

        std::map<std::string, Texture*> m_TextureMap;

        TextureCache();

    public:
        ~TextureCache();
        static TextureCache* getTextureCache();
        Texture* getTexture(std::string texturePath, fileExtension flag);
    };

}