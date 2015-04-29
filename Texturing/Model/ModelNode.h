#ifndef ModelNode_h__
#define ModelNode_h__

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <gl/glew.h>

#include "ModelMesh.h"
#include "GraphicsDevice\GraphicsDevice.h"

class ModelNode
{
	
public:
	std::string name;
	ModelNode* parent;
	std::vector<ModelNode*> children;
	std::vector<ModelMesh*> meshes;
	glm::mat4 transforms;

	ModelNode();
	~ModelNode();

	void Render(GraphicsDevice* graphicsDevice, glm::mat4 parentTransforms);
	ModelNode* FindNode(std::string name);
};

#endif // Model_h__