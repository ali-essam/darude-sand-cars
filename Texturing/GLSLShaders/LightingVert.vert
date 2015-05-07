#version 330 core


// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 inputColor;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 vertexNormal_modelspace;

// Values that stay constant for the whole mesh.
uniform mat4 M;
uniform mat4 VP;

out vec3 fragmentColor;
//Textures
out vec2 TexCoord;
out vec3 normal_worldspace;
out vec3 position_worldspace;
void main(){
	gl_Position =  VP * M * vec4(vertexPosition_modelspace,1);
	position_worldspace = vec3(M * vec4(vertexPosition_modelspace,1));
	normal_worldspace = normalize(vec3(M * vec4(vertexNormal_modelspace,0)));
	fragmentColor =  inputColor;
	TexCoord = texCoord;
}

