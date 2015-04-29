#ifndef Skybox_h__
#define Skybox_h__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <string>

#include "Model\ModelMesh.h"
#include "GraphicsDevice\GraphicsDevice.h"
#include "Texture\texture.h"


class Skybox
{
	Texture textures[5];
	ModelMesh meshes[5];
	glm::mat4 modelMats[5];
public:
	float size;

	Skybox();
	~Skybox();
	
	bool LoadFromPath(std::string path, std::string ext = "JPG");
	void Initialize();
	void Render(GraphicsDevice* graphicsDevice);
	void Cleanup();
};

#endif // Skybox_h__