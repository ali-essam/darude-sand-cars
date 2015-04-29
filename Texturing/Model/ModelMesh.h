#ifndef ModelMesh_h__
#define ModelMesh_h__

#include <glm/glm.hpp>
#include <vector>
#include <gl\glew.h>

#include "Texture\texture.h"
#include "GraphicsDevice\GraphicsDevice.h"
class ModelMesh
{
private:
	//VAO
	GLuint mVertexArrayObjectID;
	
	//VBOs
	GLuint mVertexDataBufferID;
	GLuint mColorDataBufferID;
	GLuint mIndicesDataBufferID;
	GLuint mUVDataBufferID;
	GLuint mNormalsBufferID;

public:
	ModelMesh();
	~ModelMesh();
	std::vector<glm::vec3> VertexData;
	std::vector<glm::vec3> ColorData;
	std::vector<unsigned short> IndicesData;
	std::vector<glm::vec2> UVData;
	std::vector<glm::vec3> NormalsData;
	
	Texture* texture;

	void Initialize();
	void Render(GraphicsDevice* graphicsDevice);
	void Cleanup();
};

#endif // ModelMesh_h__