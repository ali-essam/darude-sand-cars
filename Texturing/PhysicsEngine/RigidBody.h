#ifndef RigidBody_h__
#define RigidBody_h__

#include "PhysicsObject.h"

#include <glm/glm.hpp>
#include "AABoundingBox.h"

class RigidBody : public PhysicsObject
{
	glm::vec3 force; // May the force be with you.
protected:

public:
	RigidBody();
	~RigidBody();

	inline glm::vec3 GetForce() { return force; }

	void SetForce(glm::vec3 f);
	void AddForce(glm::vec3 f);
	void RemoveForce(glm::vec3 f);

	virtual void Update(float dt);
};

#endif // PhysicsObject_h__