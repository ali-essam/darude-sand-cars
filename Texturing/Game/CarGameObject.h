#ifndef CarGameObject_h__
#define CarGameObject_h__

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "PhysicsEngine\CarPhysicsObject.h"
#include "PhysicsEngine\AABoundingBox.h"
#include "Model\Model.h"
#include "GraphicsDevice\GraphicsDevice.h"

class CarGameObject
{

protected:
	AABoundingBox boundingBox;
	CarPhysicsObject physicsObject;
	Model* model;
	glm::mat4 modelMatrix;
public:
	CarGameObject(Model* model);
	~CarGameObject();


	inline AABoundingBox GetBoundingBox() { return boundingBox; }
	inline PhysicsObject* GetPhysicsObject() { return &physicsObject; }
	inline glm::vec3 GetPosition() {return physicsObject.GetPosition(); }
	inline float GetSteerAngle() { return physicsObject.GetSteerAngle(); };
	inline Model* GetModel() { return model; }

	void SetPosition(glm::vec3 position);

	void SteerRight();
	void SteerLeft();
	void Throttle();
	void Break();


	void Update(double dt);
	void Render(GraphicsDevice* graphicsDevice);
};

#endif //GenericGameObject_h__