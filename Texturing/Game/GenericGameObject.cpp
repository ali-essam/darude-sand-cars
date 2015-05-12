#include "GenericGameObject.h"

GenericGameObject::GenericGameObject(Model* model, PhysicsObject* physicsObject)
{
	this->model = model;
	this->physicsObject = physicsObject;
	this->boundingBox.SetCenter(this->physicsObject->GetPosition());
	this->boundingBox.SetSize(AABoundingBox::CalculateBoundingBoxSize(model->GetAllVerticies()));
	this->physicsObject->SetBoundingBox(&boundingBox);
}

GenericGameObject::~GenericGameObject()
{
}

void GenericGameObject::Update(double dt)
{
	
}

void GenericGameObject::Render(ModelShaderProgram* ModelShader)
{
	glm::mat4 model = glm::translate(physicsObject->GetPosition()) * modelMatrix;// * modelMatrix;//* glm::scale(0.01f, 0.01f, 0.01f);
	this->model->Render(ModelShader, model);
}

void GenericGameObject::Scale(glm::vec3 scale)
{
	this->boundingBox.Scale(scale);
	modelMatrix=glm::scale(scale) * modelMatrix;
}