#include "Mesh.h"

#include <fstream>
#include <sstream>

Mesh::Mesh() : m_Texture(nullptr), m_MaxSize(0)
{
}

Mesh::Mesh(Texture *texture) : m_VBO(0), m_VAO(0), m_EBO(0), m_MaxSize(0)
{
    m_Texture = texture;
}

Mesh::~Mesh()
{
	m_Vertices.clear();
	m_Triangles.clear();
}

bool Mesh::loadMesh(const char* filename)
{
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        return false;
    }
    std::string line;

    std::vector< glm::vec3 > tmpV;
    std::vector< glm::vec3 > tmpN;

    while (std::getline(infile, line)) {

        std::istringstream iss(line);
        std::string code;
        iss >> code;

        if (code == "v") {
            float x, y, z;
            iss >> x >> y >> z;
            tmpV.push_back(glm::vec3(x, y, z));
			findMaxSize(x, y, z);
        }
        else if (code == "vn") {
            float x, y, z;
            iss >> x >> y >> z;
            tmpN.push_back(glm::vec3(x, y, z));
        }
        else if (code == "vt") {
            float x, y;
            iss >> x >> y;
            VertexMesh newVertex;
            newVertex.uv = glm::vec2(x, 1.0f - y); // NB: flipping the y, different conventions about UV space
            // We are going to load "newVertice.pos" and "newVertice.norm" later when i read the faces
            m_Vertices.push_back(newVertex);
        }
        else if (code == "f") {
            std::string st_i, st_j, st_k;
            iss >> st_i >> st_j >> st_k;
            int i0, i1, i2;
            int j0, j1, j2;
            int k0, k1, k2;

            // Every sequence of numbers (i0, i1, i2) describes a vertex of the next face (or Triangle)
            // i0: says which vertex to use
            // i1: says which texture cordinates (UV) to use
            // i2: says which normal to use 
            sscanf_s(st_i.c_str(), "%d/%d/%d", &i0, &i1, &i2);
            sscanf_s(st_j.c_str(), "%d/%d/%d", &j0, &j1, &j2);
            sscanf_s(st_k.c_str(), "%d/%d/%d", &k0, &k1, &k2);

            // Obj indices start from 1 not 0!
            i0--; j0--; k0--;
            i1--; j1--; k1--;
            i2--; j2--; k2--;

			// Load the position and normal of every vertex
            m_Vertices[i1].pos = tmpV[i0];
            m_Vertices[i1].norm = tmpN[i2];
            m_Vertices[j1].pos = tmpV[j0];
            m_Vertices[j1].norm = tmpN[j2];
            m_Vertices[k1].pos = tmpV[k0];
            m_Vertices[k1].norm = tmpN[k2];

			// Save the position of the every vertex on the array m_Vertices
			// to use later when we build the elements array (m_EBO)
			Triangle newTriangle(i1, j1, k1);
			m_Triangles.push_back(newTriangle);
        }
    }
    return true;
}

void Mesh::loadGPUMesh(Engine::GLSLProgram* shaderProgram)
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
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(VertexMesh), &m_Vertices[0], GL_STATIC_DRAW);

    GLuint vertPos = shaderProgram->getAttrLocation("vertexPosition");
    GLuint textCord = shaderProgram->getAttrLocation("texCord");

    //The vertex attribute array needs to be enabled.
    glEnableVertexAttribArray(vertPos);
    glEnableVertexAttribArray(textCord);

    // Now we can specify how the data for that input is retrieved from the array
    glVertexAttribPointer(vertPos, 3, GL_FLOAT, GL_FALSE, sizeof(VertexMesh), 0);
    glVertexAttribPointer(textCord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexMesh), (void*)offsetof(VertexMesh, uv));

    if (m_EBO == 0) {
        glGenBuffers(1, &m_EBO);
    }

    // Create an element array
    // An element array is filled with unsigned integers referring to vertices bound to GL_ARRAY_BUFFER.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Triangles.size() * sizeof(Triangle), &m_Triangles[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    m_nElements = m_Triangles.size() * 3;
}

void Mesh::drawMesh()
{
    glBindVertexArray(m_VAO);

    if (m_Texture != nullptr) {
        glBindTexture(GL_TEXTURE_2D, m_Texture->getID());
    }

    glDrawElements(GL_TRIANGLES, m_nElements, GL_UNSIGNED_INT, 0);

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


