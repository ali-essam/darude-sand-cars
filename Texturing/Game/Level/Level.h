#ifndef Level_h__
#define Level_h__

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <string>
#include <vector>
#include <fstream>

#include "ShaderProgram\ModelShaderProgram.h"
#include "PhysicsEngine\PhysicsObject.h"
#include "Texture\texture.h"
#include "Model\ModelMesh.h"
#include "PhysicsEngine\RigidBody.h"
#include "PhysicsEngine\AABoundingBox.h"


class Level
{
	std::vector<PhysicsObject*> colliders;
	std::vector<std::string> levelMat;
	int height;
	int width;
	int startR;
	int startC;
	Texture* textures[7];
	ModelMesh* cellMesh;
	const float cellSize;
	void Initialize();
protected:
public:
	Level();
	~Level();

	glm::vec3 GetStartPosition();

	void LoadFromFile(std::string path);
	void Update(double dt);
	void Render(ModelShaderProgram* modelShader);
	std::vector<PhysicsObject*> GetPhysicsObjects();
};

#endif //Level_h__