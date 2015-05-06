#ifndef CarPhysicsObject_h__
#define CarPhysicsObject_h__

#include "PhysicsObject.h"

#include <math.h>
#include <glm/glm.hpp>
#include "AABoundingBox.h"

class CarPhysicsObject : public PhysicsObject
{
	float carSpeed;
	float wheelBase;
protected:

public:
	float carHeading;
	float steerAngle;

	CarPhysicsObject();
	~CarPhysicsObject();

	virtual void Update(float dt);
};

#endif // PhysicsObject_h__