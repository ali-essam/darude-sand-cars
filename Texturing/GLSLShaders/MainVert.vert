#version 330 core


// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 inputColor;
layout(location = 2) in vec2 texCoord;


// Values that stay constant for the whole mesh.
uniform mat4 M;
uniform mat4 VP;

out vec3 fragmentColor;
//Textures
out vec2 TexCoord;

void main(){

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  VP * M * vec4(vertexPosition_modelspace,1);
	fragmentColor = inputColor;
	TexCoord = texCoord;
}

