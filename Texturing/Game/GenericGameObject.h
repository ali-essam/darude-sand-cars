#ifndef GenericGameObject_h__
#define GenericGameObject_h__

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "PhysicsEngine\PhysicsObject.h"
#include "PhysicsEngine\AABoundingBox.h"
#include "Model\Model.h"

#include "ShaderProgram\ModelShaderProgram.h"


class GenericGameObject
{

protected:
	AABoundingBox boundingBox;
	PhysicsObject* physicsObject;
	Model* model;
	glm::mat4 modelMatrix;
public:
	GenericGameObject(Model* model, PhysicsObject* physicsObject);
	~GenericGameObject();


	inline AABoundingBox GetBoundingBox() { return boundingBox; }
	inline PhysicsObject* GetPhysicsObject() { return physicsObject; }
	inline Model* GetModel() { return model; }

	void Translate(glm::vec3 t);
	void SetPosition(glm::vec3 position);
	void Rotate(glm::vec3 angle);
	void Scale(glm::vec3 position);

	void Update(double dt);
	void Render(ModelShaderProgram* modelShader);
};

#endif //GenericGameObject_h__