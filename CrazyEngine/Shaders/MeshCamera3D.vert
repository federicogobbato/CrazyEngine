#version 150

in vec3 vertexPosition;
in vec2 texCoord;

out vec2 fragmUV;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;

void main()
{		
	gl_Position = cameraMatrix * modelMatrix * vec4(vertexPosition, 1.0);
	
	fragmUV = texCoord;
}