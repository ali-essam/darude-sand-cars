#ifndef CarGameObject_h__
#define CarGameObject_h__

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "PhysicsEngine\CarPhysicsObject.h"
#include "PhysicsEngine\AABoundingBox.h"
#include "Model\Model.h"
#include "Model\ModelNode.h"
#include "ShaderProgram\ModelShaderProgram.h"


class CarGameObject
{

protected:
	AABoundingBox boundingBox;
	CarPhysicsObject physicsObject;
	Model* model;
	ModelNode* leftWheelNode;
	ModelNode* rightWheelNode;
	glm::mat4 modelMatrix;
public:
	CarGameObject(Model* model, std::string leftWheelNodeName, std::string rightWheelNodeName);
	~CarGameObject();


	inline AABoundingBox GetBoundingBox() { return boundingBox; }
	inline PhysicsObject* GetPhysicsObject() { return &physicsObject; }
	inline glm::vec3 GetPosition() {return physicsObject.GetPosition(); }
	inline float GetSteerAngle() { return physicsObject.GetSteerAngle(); };
	inline float GetHeadingAngle() { return physicsObject.GetCarHeading(); };
	inline Model* GetModel() { return model; }

	void SetPosition(glm::vec3 position);

	void SteerRight();
	void SteerLeft();
	void Throttle();
	void Break();


	void Update(double dt);
	void Render(ModelShaderProgram* modelShader);
};

#endif //GenericGameObject_h__