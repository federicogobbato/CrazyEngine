#include "GameObject2D.h"

#include "TextureCache.h"

namespace Engine {

    GameObject2D::GameObject2D(glm::vec2 position, int depth, std::string texturePath, fileExtension textureFormat, glm::vec2 size, ColorRGBA8 color) :
        m_Position(position),
        m_Size(size),
        m_UV(0.0f, 0.0f),
        m_UVsize(1.0f, 1.0f),
        m_Color(color),
        m_Depth(float(depth)),
        m_TexturePath(texturePath)
    {
        m_Texture = TextureCache::getTextureCache()->getTexture(texturePath, textureFormat);
    }


    GameObject2D::~GameObject2D()
    {
    }

    GameObject2D::GameObject2D(const GameObject2D &copy)
    {
        m_Position = copy.m_Position;
        m_Size = copy.m_Size;
        m_UV = copy.m_UV;
        m_UVsize = copy.m_UVsize;
        m_Color = copy.m_Color;
        m_Depth = copy.m_Depth;
        m_TexturePath = copy.m_TexturePath;
        m_TextureFormat = copy.m_TextureFormat;
        m_Texture = TextureCache::getTextureCache()->getTexture(copy.m_TexturePath, m_TextureFormat);
    }

    GameObject2D& GameObject2D::operator=(const GameObject2D &param)
    {
        m_Position = param.m_Position;
        m_Size = param.m_Size;
        m_UV = param.m_UV;
        m_UVsize = param.m_UVsize;
        m_Color = param.m_Color;
        m_Depth = param.m_Depth;
        m_TexturePath = param.m_TexturePath;
        TextureCache::getTextureCache()->getTexture(param.m_TexturePath, m_TextureFormat);
        return *this;
    }

    void GameObject2D::draw(SpriteBatch &spriteBatch)
    {
        spriteBatch.draw(m_Position, m_Size, m_UV, m_UVsize, m_Texture->getID(), m_Depth, m_Color);
    }

}