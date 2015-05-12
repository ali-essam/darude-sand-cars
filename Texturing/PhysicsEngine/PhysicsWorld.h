#ifndef PhysicsWorld_h__
#define PhysicsWorld_h__

#include <vector>
#include "PhysicsObject.h"

class PhysicsWorld
{
	glm::vec3 GetVecDir(glm::vec3 v);
public:
	std::vector<PhysicsObject*> physicsObjects;
	
	PhysicsWorld();
	~PhysicsWorld();

	void Update(float dt);
};

#endif // PhysicsWorld_h__