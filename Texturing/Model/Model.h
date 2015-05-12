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
#include "ShaderProgram\ModelShaderProgram.h"


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
	void Render(ModelShaderProgram* modelShader);
	void Render(ModelShaderProgram* modelShader, glm::mat4 transformationMatrix);
	void Cleanup();

	std::vector<glm::vec3> GetAllVerticies();
	ModelNode* FindNode(std::string name);
};
#endif // Model_h__

