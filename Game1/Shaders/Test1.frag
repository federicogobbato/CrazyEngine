#version 150

uniform float time;

in vec3 fragmColor;

out vec4 outColor;

void main()
{
    outColor = vec4(fragmColor * time, 1.0);
}