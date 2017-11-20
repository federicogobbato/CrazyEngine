#version 150

in vec3 vertexPosition;
in vec2 texCord;

out vec2 fragmtexCord;

uniform mat4 cameraMatrix;

void main()
{		
	gl_Position = cameraMatrix * vec4(vertexPosition, 1.0);
	
	fragmtexCord = texCord;
}