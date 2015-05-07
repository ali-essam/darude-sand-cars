#version 330 core

// input data
in vec3 fragmentColor;
in vec2 TexCoord;
in vec3 position_worldspace;
in vec3 normal_worldspace;

uniform vec3 directionalLightColor;
uniform vec3 directionalLightDirection;
uniform vec3 ambientLightColor;



// Ouput data
out vec3 color;

//texture sampler
uniform sampler2D myTextureSampler;

void main()
{
	float DiffuseFactor = dot(directionalLightDirection, normal_worldspace);

	vec3 DiffuseColor;

    if (DiffuseFactor > 0) {
        DiffuseColor = directionalLightColor * DiffuseFactor;
    }
    else {
        DiffuseColor = vec3(0, 0, 0);
    }
	
	vec3 FragColor = texture(myTextureSampler, TexCoord).rgb;

	color = FragColor * (DiffuseColor);// + specular;ambientLightColor + 
}