#include "Mesh.h"

#include <sstream>

namespace Engine {

    Mesh::Mesh() : m_Texture(nullptr), m_MaxSize(0)
    {
    }

    Mesh::Mesh(Texture *texture) : m_VBO(0), m_VAO(0), m_EBO(0), m_MaxSize(0)
    {
        m_Texture = texture;
    }

    Mesh::~Mesh()
    {
        delete[] m_Vertices;
        delete[] m_Triangles;
    }

    bool Mesh::readMeshFile(const char* filename)
    {
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            return false;
        }
        std::string line;
        std::string code;

        std::vector<glm::vec3> tmpV;
        std::vector<glm::vec3> tmpN;
        std::vector<glm::vec2> tmpVT;

        while (std::getline(infile, line)) 
        {
            std::istringstream iss(line);
            iss >> code;

            if (code == "v") // vertex position
            {
                float x, y, z;
                iss >> x >> y >> z;
                tmpV.push_back(glm::vec3(x, y, z));
                findMaxSize(x, y, z);
            }
            else if (code == "vt") // vertex texture
            {
                float x, y;
                iss >> x >> y;
                Vertex3D newVertex;
                tmpVT.push_back(glm::vec2(x, 1.0f - y)); // flipped the y, different conventions about UV space
            }
            else if (code == "vn") // vertex normal
            {
                float x, y, z;
                iss >> x >> y >> z;
                tmpN.push_back(glm::vec3(x, y, z));
            }
            else if (tmpVT.size() > 0 && tmpV.size() > 0 && tmpN.size())
            {
                break;
            }
        }

        m_nVertexTexture = tmpVT.size();
        m_Vertices = new Vertex3D[m_nVertexTexture];

        for(int i = 0; i < m_nVertexTexture; ++i)
        {
            m_Vertices[i].uv = tmpVT[i];
        }

        std::vector<Triangle> tmpTR;

        while (std::getline(infile, line))
        {
            std::istringstream iss(line);
            iss >> code;

            if (code == "f") 
            {
                char st_i[20];
                char st_j[20];
                char st_k[20];
                iss >> st_i >> st_j >> st_k;
                int i0, i1, i2;
                int j0, j1, j2;
                int k0, k1, k2;

                // Every sequence of numbers (i0, i1, i2) describes a vertex of the a face (or Triangle)
                // i0: says which vertex 
                // i1: says which texture cordinates (UV) 
                // i2: says which normal 
                sscanf_s(st_i, "%d/%d/%d", &i0, &i1, &i2);
                sscanf_s(st_j, "%d/%d/%d", &j0, &j1, &j2);
                sscanf_s(st_k, "%d/%d/%d", &k0, &k1, &k2);

                // Obj indices start from 1 not 0!
                --i0; --j0; --k0;
                i1--; j1--; k1--;
                i2--; j2--; k2--;

                // Save the position and normal of every vertex
                m_Vertices[i1].pos = tmpV[i0];
                m_Vertices[i1].norm = tmpN[i2];
                m_Vertices[j1].pos = tmpV[j0];
                m_Vertices[j1].norm = tmpN[j2];
                m_Vertices[k1].pos = tmpV[k0];
                m_Vertices[k1].norm = tmpN[k2];

                // Save the position of the every vertex on another array to use later when we build the elements array (m_EBO)
                Triangle newTriangle(i1, j1, k1);
                tmpTR.push_back(newTriangle);
            }

            m_nTriangles = tmpTR.size();
            m_Triangles = new Triangle[m_nTriangles];

            for (int i = 0; i < m_nTriangles; ++i)
            {
                m_Triangles[i] = tmpTR[i];
            }
        } 

        return true;
    }

    void Mesh::createGPUMesh(GLSLProgram* shaderProgram)
    {
        if (m_VAO == 0) {
            glGenVertexArrays(1, &m_VAO);
        }

        glBindVertexArray(m_VAO);

        if (m_VBO == 0) {
            // We need a Vertec Buffer Object to upload the vertex data to the graphics card
            glGenBuffers(1, &m_VBO); //Generate 1 buffer 
        }

        // To upload the actual data we need yo make m_VBO the active object
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        // Now we can copy the vertex data to m_VBO
        glBufferData(GL_ARRAY_BUFFER, m_nVertexTexture * sizeof(Vertex3D), &m_Vertices[0], GL_STATIC_DRAW);

        GLuint vertPos = shaderProgram->getAttrLocation("vertexPosition");
        GLuint textCord = shaderProgram->getAttrLocation("texCord");

        //The vertex attribute array needs to be enabled.
        glEnableVertexAttribArray(vertPos);
        glEnableVertexAttribArray(textCord);

        // Now we can specify how the data for that input is retrieved from the array
        glVertexAttribPointer(vertPos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), 0);
        glVertexAttribPointer(textCord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, uv));

        if (m_EBO == 0) {
            glGenBuffers(1, &m_EBO);
        }

        // Create an element array
        // An element array is filled with unsigned integers referring to vertices bound to GL_ARRAY_BUFFER.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_nTriangles * sizeof(Triangle), &m_Triangles[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

    void Mesh::drawMesh()
    {
        glBindVertexArray(m_VAO);

        if (m_Texture != nullptr) {
            glBindTexture(GL_TEXTURE_2D, m_Texture->getID());
        }

        glDrawElements(GL_TRIANGLES, m_nTriangles * sizeof(Triangle), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }

    void Mesh::findMaxSize(float &x, float &y, float &z)
    {
        if (x > m_MaxSize.x) {
            m_MaxSize.x = x;
        }

        if (y > m_MaxSize.y) {
            m_MaxSize.y = y;
        }

        if (z > m_MaxSize.z) {
            m_MaxSize.z = z;
        }
    }

}

