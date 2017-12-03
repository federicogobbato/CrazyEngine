#pragma once

#include <string>
#include <glm.hpp>

#include "SpriteBatch.h"
#include "TextureCache.h"

namespace Engine {

    class GameObject2D
    {
    public:
        GameObject2D(glm::vec2 position, int depth, std::string texturePath, fileExtension textureFormat,
                    glm::vec2 size, ColorRGBA8 color = defaultColor());
        ~GameObject2D();

        GameObject2D(const GameObject2D &copy);
        GameObject2D& operator= (const GameObject2D &param);

        //setters
        void setPosition(float &x, float &y) {
            m_Position.x = x;
            m_Position.y = y;
        }

        void setPosition(glm::vec2 newPosition) {
            m_Position = newPosition;
        }

        //getters
        const glm::vec2& getPosition() const {
            return m_Position;
        }
        const glm::vec2& getSize() const {
            return m_Size;
        }

        void draw(SpriteBatch &spriteBatch);

    protected:
        glm::vec2 m_Position;
        glm::vec2 m_Size;
        glm::vec2 m_UV;
        glm::vec2 m_UVsize;
        ColorRGBA8 m_Color;
        float m_Depth;
        Texture* m_Texture;

        std::string m_TexturePath;
        fileExtension m_TextureFormat;
    };

}



