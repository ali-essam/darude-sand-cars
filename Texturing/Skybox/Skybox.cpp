#include "Skybox.h"

Skybox::Skybox():size(10000.0f)
{
}

Skybox::~Skybox()
{
}

void Skybox::Initialize()
{
	for (int i = 0; i < 5; i++)
	{
		meshes[i].VertexData.push_back(glm::vec3(-size, -size, 0.0f));
		meshes[i].VertexData.push_back(glm::vec3(-size, size, 0.0f));
		meshes[i].VertexData.push_back(glm::vec3(size, -size, 0.0f));
		meshes[i].VertexData.push_back(glm::vec3(size, size, 0.0f));

		meshes[i].ColorData.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		meshes[i].ColorData.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
		meshes[i].ColorData.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
		meshes[i].ColorData.push_back(glm::vec3(0.0f, 0.0f, 1.0f));

		meshes[i].IndicesData.push_back(0);
		meshes[i].IndicesData.push_back(1);
		meshes[i].IndicesData.push_back(2);
		meshes[i].IndicesData.push_back(1);
		meshes[i].IndicesData.push_back(2);
		meshes[i].IndicesData.push_back(3);

		meshes[i].UVData.push_back(glm::vec2(1.0f, 1.0f));
		meshes[i].UVData.push_back(glm::vec2(1.0f, 0.0f));
		meshes[i].UVData.push_back(glm::vec2(0.0f, 1.0f));
		meshes[i].UVData.push_back(glm::vec2(0.0f, 0.0f));

		meshes[i].NormalsData.assign(4, glm::vec3(0.0, 0.0, 1.0));

		meshes[i].texture = &textures[i];

		meshes[i].Initialize();
	}
	// TODO: Clean Code
	modelMats[0] = glm::translate(0.0f, 0.0f, -size);
	modelMats[1] = glm::translate(0.0f, 0.0f, size) * glm::rotate(180.f, glm::vec3(0, 1, 0));

	glm::mat4 rotationMatrix = glm::rotate(90.f, glm::vec3(0, 1, 0));
	glm::mat4 rotationMatrixI = glm::rotate(-90.f, glm::vec3(0, 1, 0));
	
	glm::mat4 translateMatrix = glm::translate(size, .0f, .0f);
	modelMats[2] = translateMatrix * rotationMatrixI;

	translateMatrix = glm::translate(-size, .0f, .0f);
	modelMats[3] = translateMatrix * rotationMatrix;

	rotationMatrix = glm::rotate(90.f, glm::vec3(1, 0, 0));
	translateMatrix = glm::translate(.0f, size, .0f);
	modelMats[4] = translateMatrix * rotationMatrix;
}

bool Skybox::LoadFromPath(std::string path, std::string ext)
{
	bool loaded = true;
	for (int i = 0; i < 5; i++)
	{
		std::string texPath = path + (char)(i+'0') + "." + ext;
		bool texLoaded = textures[i].LoadFromFile(texPath, 0);
		if(!texLoaded)
			printf("Unable to load skybox texture: %s", texPath.c_str());
		loaded &= texLoaded;
	}
	return loaded;
}

void Skybox::Render(ModelShaderProgram* modelShader)
{
	for (int i = 0; i < 5; i++)
	{
		modelShader->BindModelMatrix(&modelMats[i][0][0]);
		meshes[i].Render();
	}
}