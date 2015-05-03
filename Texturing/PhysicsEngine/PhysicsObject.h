#ifndef PhysicsObject_h__
#define PhysicsObject_h__

#include <glm/glm.hpp>
#include "AABoundingBox.h"

class PhysicsObject
{

protected:
	glm::vec3 position;
	glm::vec3 velocity;
	float mass;

	AABoundingBox* boundingBox;
public:
	PhysicsObject();
	~PhysicsObject();

	inline float GetMass() { return mass; }
	inline glm::vec3 GetVelocity() { return velocity; }
	inline glm::vec3 GetPosition() { return position; }
	inline AABoundingBox* GetBoundingBox() { return boundingBox; }

	void SetMass(float m);
	void SetVelocity(glm::vec3 velocity);
	void SetPosition(glm::vec3 position);
	void Translate(glm::vec3 dist);
	void SetBoundingBox(AABoundingBox* boundingBox);

	
	virtual void Update(float dt) {};
};

#endif // PhysicsObject_h__