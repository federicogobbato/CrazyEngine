#pragma once

#include "CoreMinimal.h"


namespace Engine {

    class Mesh
    {
        Vertex3D* m_Vertices;
        Triangle* m_Triangles;

        GLuint m_VBO; // Vertex Buffer Object
        GLuint m_VAO; // Vertex Array Object
        GLuint m_EBO; // Element array

        Texture* m_Texture;

        int m_nVertexTexture;
        int m_nTriangles;

        glm::vec3 m_MaxSize;

    public:

        Mesh();
        Mesh(Texture* texture);
        ~Mesh();

        void setTexture(Texture* texture)
        {
            m_Texture = texture;
        }

        glm::vec3 getMaxSize() {
            return m_MaxSize;
        }

        bool readMeshFile(const char* path);

        void createGPUMesh(GLSLProgram* shaderProgram);

        void drawMesh();

        void findMaxSize(float &x, float &y, float &z);
    };

}
