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

void GenericGameObject::Render(GraphicsDevice* graphicsDevice)
{
	glm::mat4 model = glm::translate(physicsObject->GetPosition());// * modelMatrix;//* glm::scale(0.01f, 0.01f, 0.01f);
	this->model->Render(graphicsDevice, model);
}