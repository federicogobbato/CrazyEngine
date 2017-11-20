#include "SpriteBatch.h"

#include <algorithm>

namespace Engine {

    SpriteBatch::SpriteBatch() : m_VBO(0), m_VAO(0)
    {

    }


    SpriteBatch::~SpriteBatch()
    {
    }

    void SpriteBatch::init()
    {
        createVertexArray();
    }

    void SpriteBatch::begin(GlyphSortType sortType)
    {
        m_SortType = sortType;
        m_RenderBatches.clear();
        m_Glyphs.clear();
    }

    void SpriteBatch::end()
    {
        m_GlyphsPointers.resize(m_Glyphs.size());
        for (int i = 0; i < m_Glyphs.size(); i++) {
            m_GlyphsPointers[i] = &m_Glyphs[i];
        }
        sortGlyphs();
        createRenderBatches();
    }


    void SpriteBatch::draw(const glm::vec2& position, const glm::vec2& size, 
                    const glm::vec2& UV, const glm::vec2& UVsize, const GLuint& texture, const float& depth, const ColorRGBA8 & color)
    {
        m_Glyphs.emplace_back(position, size, UV, UVsize, texture, depth, color);
    }


    void SpriteBatch::renderBatch()
    { 
        glBindVertexArray(m_VAO);

        for (int i = 0; i < m_RenderBatches.size(); i++) {
            glBindTexture(GL_TEXTURE_2D, m_RenderBatches[i].m_Texture);
            // Draw the vertices to the screen.
            glDrawArrays(GL_TRIANGLES, m_RenderBatches[i].m_Offset, m_RenderBatches[i].m_NumVertex);
        }

        glBindVertexArray(0);
    }


    void SpriteBatch::createRenderBatches()
    {
        // This will store all the vertices that we need to upload
        std::vector <Vertex> vertices;
        vertices.resize((m_Glyphs.size() * 6));

        if (m_Glyphs.empty()) {
            return;
        }

        int offset = 0;
        int cv = 0;

        //Add the first batch
        m_RenderBatches.emplace_back(offset, 6, m_GlyphsPointers[0]->texture);
        vertices[cv++] = m_GlyphsPointers[0]->topLeft;
        vertices[cv++] = m_GlyphsPointers[0]->bottomLeft;
        vertices[cv++] = m_GlyphsPointers[0]->bottomRight;
        vertices[cv++] = m_GlyphsPointers[0]->bottomRight;
        vertices[cv++] = m_GlyphsPointers[0]->topRight;
        vertices[cv++] = m_GlyphsPointers[0]->topLeft;
        offset += 6;

        //Add all the rest of the glyphs
        for (int cg = 1; cg < m_GlyphsPointers.size(); cg++)
        {
            // Check if this glyph can be part of the current batch
            if (m_GlyphsPointers[cg]->texture != m_GlyphsPointers[cg - 1]->texture) {
                // Make a new batch
                m_RenderBatches.emplace_back(offset, 6, m_GlyphsPointers[cg]->texture);
            }
            else
            {
                // If its part of the current batch, just increase numVertices
                m_RenderBatches.back().m_NumVertex += 6;
            }
            vertices[cv++] = m_GlyphsPointers[cg]->topLeft;
            vertices[cv++] = m_GlyphsPointers[cg]->bottomLeft;
            vertices[cv++] = m_GlyphsPointers[cg]->bottomRight;
            vertices[cv++] = m_GlyphsPointers[cg]->bottomRight;
            vertices[cv++] = m_GlyphsPointers[cg]->topRight;
            vertices[cv++] = m_GlyphsPointers[cg]->topLeft;
            offset += 6;
        }

        // Bind our VBO
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        // Creates a new data store for a buffer object (In this case the buffer object currently bound to target is used)
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


    void SpriteBatch::createVertexArray()
    {
        if (m_VAO == 0) {
            glGenVertexArrays(1, &m_VAO);
        }
        
        glBindVertexArray(m_VAO);

        if (m_VBO == 0) {
            glGenBuffers(1, &m_VBO);
        }

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        // Enable the generic vertex attribute array specified by index
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        // This is the position attribute pointer 
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        // This is the color attribute pointer 
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        // This is the UV attribute pointer  
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);   
    }


    void SpriteBatch::sortGlyphs()
    {
        switch (m_SortType)
        {
            case GlyphSortType::BACK_TO_FRONT:
                std::stable_sort(m_GlyphsPointers.begin(), m_GlyphsPointers.end(), compareBackToFront);
                break;
            case GlyphSortType::FRONT_TO_BACK:
                std::stable_sort(m_GlyphsPointers.begin(), m_GlyphsPointers.end(), compareFrontToBack);
                break;
            case GlyphSortType::TEXTURE:
                std::stable_sort(m_GlyphsPointers.begin(), m_GlyphsPointers.end(), compareTexture);
                break;
        }
    }


    bool SpriteBatch::compareFrontToBack(Glyph *a, Glyph *b)
    {
        return (a->depth < b->depth);
    }

    bool SpriteBatch::compareBackToFront(Glyph *a, Glyph *b)
    {
        return (a->depth > b->depth);
    }

    bool SpriteBatch::compareTexture(Glyph *a, Glyph *b)
    {
        return (a->texture < b->texture);
    }



}


