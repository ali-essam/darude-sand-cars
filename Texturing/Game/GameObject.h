#ifndef GameObject_h__
#define GameObject_h__

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "PhysicsEngine\RigidBody.h"
#include "PhysicsEngine\AABoundingBox.h"
#include "Model\Model.h"
#include "GraphicsDevice\GraphicsDevice.h"

class GameObject
{
public:
	AABoundingBox boundingBox;

	RigidBody physicsObject;
	Model* model;

	GameObject();
	~GameObject();

	void Initialize();

	void Update(double dt);
	void Render(GraphicsDevice* graphicsDevice);
};

#endif //GameObject_h__