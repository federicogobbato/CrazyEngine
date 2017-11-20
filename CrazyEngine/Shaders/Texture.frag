#version 150

in vec3 fragmColor;
in vec2 fragmtexCord;

out vec4 outColor;

uniform sampler2D tex1;
uniform sampler2D tex2;

uniform float weight;

void main()
{
    //outColor = texture(tex1, fragmtexCord) * vec4(fragmColor, 1.0);
	
	// Adding distortion to simulate water
	//if (fragmtexCord.y < 0.5)
	//{
		//outColor = texture(tex1, fragmtexCord);
	//}
	//else{
		//outColor = texture(tex1,
			//vec2(fragmtexCord.x + sin(fragmtexCord.y * 60.0 + weight * 2.0) / 30.0, 1.0 - fragmtexCord.y)) 
			//* vec4(0.7, 0.7, 1.0, 1.0);	
	//}

	// Mix Texture1 with Texture2
	vec4 coltex1 = texture(tex1, fragmtexCord);
    vec4 coltex2 = texture(tex2, fragmtexCord);
    outColor = mix(coltex1, coltex2, weight);
}