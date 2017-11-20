#version 150

in vec2 fragmUV;

out vec4 outColor;

uniform sampler2D myTexute;

void main()
{
    outColor = texture(myTexute, fragmUV) * vec4(1.0, 1.0, 1.0, 1.0);
}