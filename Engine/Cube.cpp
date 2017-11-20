
#include "Cube.h"



Cube::Cube(Texture* texture) :  m_VBO(0), m_VAO(0), m_EBO(0)
{
	m_Texture = texture;
}


Cube::~Cube()
{
}

void Cube::Init(Engine::GLSLProgram* shaderProgram, float x, float y, float z)
{
	m_MaxSize.x = x;
	m_MaxSize.y = y;
	m_MaxSize.z = z;

	m_Vertices[0].x = -x;
	m_Vertices[0].y = -y;
	m_Vertices[0].z = -z;
	m_Vertices[0].uv.x = 1;
	m_Vertices[0].uv.y = 0;

	m_Vertices[1].x = x;
	m_Vertices[1].y = -y;
	m_Vertices[1].z = -z;
	m_Vertices[1].uv.x = 0;
	m_Vertices[1].uv.y = 0;

	m_Vertices[2].x = -x;
	m_Vertices[2].y = y;
	m_Vertices[2].z = -z;
	m_Vertices[2].uv.x = 1;
	m_Vertices[2].uv.y = 1;

	m_Vertices[3].x = x;
	m_Vertices[3].y = y;
	m_Vertices[3].z = -z;
	m_Vertices[3].uv.x = 0;
	m_Vertices[3].uv.y = 1;

	m_Vertices[4].x = -x;
	m_Vertices[4].y = -y;
	m_Vertices[4].z = z;
	m_Vertices[4].uv.x = 0;
	m_Vertices[4].uv.y = 0;

	m_Vertices[5].x = x;
	m_Vertices[5].y = -y;
	m_Vertices[5].z = z;
	m_Vertices[5].uv.x = 1;
	m_Vertices[5].uv.y = 0;

	m_Vertices[6].x = -x;
	m_Vertices[6].y = y;
	m_Vertices[6].z = z;
	m_Vertices[6].uv.x = 0;
	m_Vertices[6].uv.y = 1;

	m_Vertices[7].x = x;
	m_Vertices[7].y = y;
	m_Vertices[7].z = z;
	m_Vertices[7].uv.x = 1;
	m_Vertices[7].uv.y = 1;

	// Vertex 0'
	m_Vertices[8].x = -x;
	m_Vertices[8].y = -y;
	m_Vertices[8].z = -z;
	m_Vertices[8].uv.x = 0;
	m_Vertices[8].uv.y = 1;

	// Vertex 1'
	m_Vertices[9].x = x;
	m_Vertices[9].y = -y;
	m_Vertices[9].z = -z;
	m_Vertices[9].uv.x = 1;
	m_Vertices[9].uv.y = 1;

	// Vertex 2'
	m_Vertices[10].x = -x;
	m_Vertices[10].y = y;
	m_Vertices[10].z = -z;
	m_Vertices[10].uv.x = 0;
	m_Vertices[10].uv.y = 0;

	// Vertex 3'
	m_Vertices[11].x = x;
	m_Vertices[11].y = y;
	m_Vertices[11].z = -z;
	m_Vertices[11].uv.x = 1;
	m_Vertices[11].uv.y = 0;

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
	// GL_STATIC_DRAW: The vertex data will be uploaded once and drawn many times(e.g.the world).
	// GL_DYNAMIC_DRAW : The vertex data will be changed from time to time, but drawn many times more than that.
	// GL_STREAM_DRAW : The vertex data will change almost every time it's drawn (e.g. user interface).
	// This usage value will determine in what kind of memory the data is stored on your graphics card for the highest efficiency.
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);

	if (m_EBO == 0) {
		glGenBuffers(1, &m_EBO);
	}

	// Create an element array
	// An element array is filled with unsigned integers referring to vertices bound to GL_ARRAY_BUFFER.
	GLuint elements[] = {
		0, 1, 2,
		2, 3, 1,
		0, 2, 6,
		0, 4, 6,
		4, 5, 6,
		5, 7, 6,
		1, 3, 5, 
		3, 5, 7,
		10, 6, 11,
		11, 7, 6,
		8, 4, 9,
		9, 4, 5
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	GLuint vertPos = shaderProgram->getAttrLocation("vertexPosition");
	GLuint textCord = shaderProgram->getAttrLocation("texCord");

	//The vertex attribute array needs to be enabled.
	glEnableVertexAttribArray(vertPos);
	glEnableVertexAttribArray(textCord);

	// Now we can specify how the data for that input is retrieved from the array
	//The first parameter references the input.
	//The second parameter specifies the number of values for that input, which is the same as the number of components of the vec.
	//The third parameter specifies the type of each component and the fourth parameter specifies whether the input values should be normalized between - 1.0 and 1.0 (or 0.0 and 1.0 depending on the format) if they aren't floating point numbers.
	//The last two parameters are arguably the most important here as they specify how the attribute is laid out in the vertex array.
	//The first number specifies the stride, or how many bytes are between each position attribute in the array.
	//The value 0 means that there is no data in between.This is currently the case as the position of each vertex is immediately followed by the position of the next vertex.
	//The last parameter specifies the offset, or how many bytes from the start of the array the attribute occurs.
	//Since there are no other attributes, this is 0 as well.
	glVertexAttribPointer(vertPos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), 0);
	glVertexAttribPointer(textCord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, uv));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Cube::draw()
{
	glBindVertexArray(m_VAO);

	glBindTexture(GL_TEXTURE_2D, m_Texture->getID());

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
