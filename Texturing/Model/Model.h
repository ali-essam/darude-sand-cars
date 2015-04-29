#ifndef Model_h__
#define Model_h__

#include <string>

#include <glm/glm.hpp>
#include <vector>
#include <gl\glew.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ModelMesh.h"
#include "ModelNode.h"
#include "Texture/texture.h"
#include "GraphicsDevice\GraphicsDevice.h"

class Model
{
	std::vector<ModelMesh*> meshes;
	std::vector<Texture*> textures;
	ModelNode* rootNode;

	std::string GetDirectoryPath(std::string sFilePath);
	ModelMesh* processMesh(aiMesh* aimesh);
	Texture* processMaterial(aiMaterial* aimaterial, std::string dir);
	ModelNode* processNode(aiNode* ainode, ModelNode* parent);
	glm::mat4 aiMat4x4ToglmMat4(aiMatrix4x4 aimat);
public:
	Model();
	~Model();

	bool LoadFromFile(std::string modelFileName, bool flipUVs = true);
	void Initialize();
	void Render(GraphicsDevice* graphicsDevice);
	void Render(GraphicsDevice* graphicsDevice, glm::mat4 transformationMatrix);
	void Cleanup();

};
#endif // Model_h__

