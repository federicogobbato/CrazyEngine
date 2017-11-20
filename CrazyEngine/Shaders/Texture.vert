#version 150

in vec2 vertexPosition;
in vec3 Colors;
in vec2 texCoord;

out vec3 fragmColor;
out vec2 fragmtexCord;

void main()
{		
	gl_Position = vec4(vertexPosition, 0.0, 1.0);
	
	fragmColor = Colors;
	fragmtexCord = texCoord;
}