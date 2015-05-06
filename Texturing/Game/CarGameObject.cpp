#include "CarGameObject.h"

CarGameObject::CarGameObject(Model* model, CarPhysicsObject* physicsObject)
{
	this->model = model;
	this->physicsObject = physicsObject;
	this->boundingBox.SetCenter(this->physicsObject->GetPosition());
	this->boundingBox.SetSize(AABoundingBox::CalculateBoundingBoxSize(model->GetAllVerticies()));
	this->physicsObject->SetBoundingBox(&boundingBox);
}

CarGameObject::~CarGameObject()
{
}

void CarGameObject::Update(double dt)
{
	float angle = physicsObject->steerAngle;
	if(angle>0.01f)
		angle -= 0.01/2.f;
	else if(angle<-0.01f)
		angle += 0.01/2.f;
	physicsObject->steerAngle = angle;
}

void CarGameObject::Render(GraphicsDevice* graphicsDevice)
{
	glm::mat4 model = glm::translate(physicsObject->GetPosition()) * glm::rotate(-(physicsObject->carHeading * 180.f / 3.14f - 90.f), glm::vec3(0,1,0));
	this->model->Render(graphicsDevice, model);
}