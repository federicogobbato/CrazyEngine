#pragma once

#include <vector>
#include <glm.hpp>
#include "Vertex.h"

namespace Engine {

    // Determines how we should sort the glyphs
    enum class GlyphSortType {
        NONE,
        FRONT_TO_BACK,
        BACK_TO_FRONT,
        TEXTURE
    };


    //Single Sprite
    struct Glyph {

        Glyph() {};
        Glyph(const glm::vec2& position, const glm::vec2& size,
                const glm::vec2& UV, const glm::vec2& UVsize, 
                const GLuint& Texture, const float& Depth, const ColorRGBA8 & color) :
            texture(Texture), depth(Depth)
        {
            topLeft.color = color;
            topLeft.setPosition(position.x, position.y + size.y);
            topLeft.setUV(UV.x, UV.y + UVsize.y);

            bottomLeft.color = color;
            bottomLeft.setPosition(position.x, position.y);
            bottomLeft.setUV(UV.x, UV.y);

            bottomRight.color = color;
            bottomRight.setPosition(position.x + size.x, position.y);
            bottomRight.setUV(UV.x + UVsize.x, UV.y);

            topRight.color = color;
            topRight.setPosition(position.x + size.x, position.y + size.y);
            topRight.setUV(UV.x + UVsize.x, UV.y + UVsize.y);
        }

        GLuint texture;
        float depth;

        Vertex topLeft;
        Vertex bottomLeft;
        Vertex topRight;
        Vertex bottomRight;
    };


    class RenderBatch {
    public:
        RenderBatch(GLuint offset, GLuint numVertex, GLuint texture) : 
            m_Offset(offset), m_NumVertex(numVertex), m_Texture(texture)
        {
        }
        GLuint m_Offset;
        GLuint m_NumVertex;
        GLuint m_Texture;
    };


    class SpriteBatch
    {
    public:
        SpriteBatch();
        ~SpriteBatch();

        void init();
        void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
        void end();

        // Adds a glyph to the spritebatch
        void draw (const glm::vec2& position, const glm::vec2& size,
            const glm::vec2& UV, const glm::vec2& UVsize, const GLuint& texture, const float& depth, const ColorRGBA8 & color);

        // Renders the entire SpriteBatch to the screen
        void renderBatch();

    private:
        // Creates all the needed RenderBatches
        void createRenderBatches();
        // Generates our VAO and VBO
        void createVertexArray();
        void sortGlyphs();

        static bool compareFrontToBack(Glyph* a, Glyph* b);
        static bool compareBackToFront(Glyph* a, Glyph* b);
        static bool compareTexture(Glyph* a, Glyph* b);

        GLuint m_VBO; // Vertex Buffer GameObject
        GLuint m_VAO; // Vertex Array GameObject

        GlyphSortType m_SortType;

        std::vector<Glyph*> m_GlyphsPointers;  // This is for sorting
        std::vector<Glyph> m_Glyphs;  // These are the actual gliphs
        std::vector<RenderBatch> m_RenderBatches;
    };

}



