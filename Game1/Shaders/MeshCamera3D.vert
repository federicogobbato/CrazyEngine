#version 150

in vec3 vertexPosition;
in vec2 texCord;

out vec2 fragmUV;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix[100];

uniform int ID;

void main()
{		
	gl_Position = cameraMatrix * modelMatrix[ID] * vec4(vertexPosition, 1.0);
	
	fragmUV = texCord;
}