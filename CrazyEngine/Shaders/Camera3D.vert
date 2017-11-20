#version 150

in vec2 vertexPosition;
in vec3 Colors;
in vec2 texCoord;

out vec3 fragmColor;
out vec2 fragmtexCord;

uniform mat4 cameraMatrix;
uniform mat4 rotationMatrix;

void main()
{		
	gl_Position = cameraMatrix * rotationMatrix * vec4(vertexPosition, 0.0, 1.0);
	
	fragmColor = Colors;
	fragmtexCord = texCoord;
}