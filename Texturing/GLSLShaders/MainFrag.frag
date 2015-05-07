#version 330 core

// input data
in vec3 fragmentColor;
in vec2 TexCoord;

// Ouput data
out vec3 color;

//texture sampler
uniform sampler2D myTextureSampler;

void main()
{
		color = texture( myTextureSampler, TexCoord ).rgb;
}