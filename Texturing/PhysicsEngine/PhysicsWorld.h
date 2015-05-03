#ifndef PhysicsWorld_h__
#define PhysicsWorld_h__

#include <vector>
#include "PhysicsObject.h"

class PhysicsWorld
{

public:
	std::vector<PhysicsObject*> physicsObjects;
	
	PhysicsWorld();
	~PhysicsWorld();

	void Update(float dt);
};

#endif // PhysicsWorld_h__