#include "TextureCache.h"

#include <iostream>
#include "Core.h"


TextureCache* TextureCache::m_TextureCache = nullptr;

TextureCache::TextureCache()
{
}

TextureCache * TextureCache::getTextureCache()
{
	if (m_TextureCache == nullptr) {
		m_TextureCache = new TextureCache;
	}
	return m_TextureCache;
}


TextureCache::~TextureCache()
{
	for each (auto var in m_TextureMap)
	{
		delete var.second;
	}
	delete m_TextureCache;
}

Texture* TextureCache::getTexture(std::string texturePath, fileExtension flag) {

    auto it = m_TextureMap.find(texturePath);

    if (it == m_TextureMap.end())
    {
        if (fileExist(texturePath)) 
        {
            Texture* newTexture = new Texture;
            newTexture->loadData(texturePath, flag);
            std::pair<std::string, Texture*> newPair(texturePath, newTexture);
            m_TextureMap.insert(newPair);
            //std::cout << "Used Cached Texture" << std::endl;
            return newTexture;
        }
        else {
            std::cout << texturePath << "  texture not loaded" << std::endl;
            return nullptr;
        }
    }

    //std::cout << "Loaded Texture" << std::endl;
    return it->second;
}

