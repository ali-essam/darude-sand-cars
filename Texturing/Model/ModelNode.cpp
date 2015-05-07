#include "ModelNode.h"


ModelNode::ModelNode(void)
{
}


ModelNode::~ModelNode(void)
{
}

void ModelNode::Render(ModelShaderProgram* modelShader, glm::mat4 parentTransforms)
{
	glm::mat4 curTransform = parentTransforms * this->transforms;
	//glm::mat4 curTransform = parentTransforms;
	modelShader->BindModelMatrix(&curTransform[0][0]);
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Render();
	}
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->Render(modelShader, curTransform);
	}
}

ModelNode* ModelNode::FindNode(std::string name)
{
	// Not Tested.
	if(this->name == name)
		return this;
	ModelNode* node = 0;
	for (int i = 0; i < children.size(); i++)
	{
		if(node = children[i]->FindNode(name))
			return node;
	}
	return node;
}