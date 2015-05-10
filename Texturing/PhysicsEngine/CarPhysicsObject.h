#ifndef CarPhysicsObject_h__
#define CarPhysicsObject_h__

#include "PhysicsObject.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>
#include "AABoundingBox.h"

class CarPhysicsObject : public PhysicsObject
{
	const float engineForce;
	const float breakForce;
	const float maxCarSpeed;
	const float maxSteerAngle;
	float carSpeed;
	float wheelBase;
	float carHeading;
	float steerAngle;

	bool steeringLeft;
	bool steeringRight;
	bool throttling;
	bool breaking;

	void ResetControls();
protected:

public:
	inline float GetCarHeading() { return carHeading; }
	inline float GetSteerAngle() { return steerAngle; }

	void SteerRight();
	void SteerLeft();
	void Throttle();
	void Break();

	CarPhysicsObject();
	~CarPhysicsObject();

	virtual void Update(float dt);
};

#endif // PhysicsObject_h__