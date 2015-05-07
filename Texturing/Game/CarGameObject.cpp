#include "CarGameObject.h"

CarGameObject::CarGameObject(Model* model)
{
	this->model = model;
	this->boundingBox.SetCenter(this->physicsObject.GetPosition());
	this->boundingBox.SetSize(AABoundingBox::CalculateBoundingBoxSize(model->GetAllVerticies()));
	this->physicsObject.SetBoundingBox(&boundingBox);
}

CarGameObject::~CarGameObject()
{
}

void CarGameObject::Update(double dt)
{
	float angle = physicsObject.GetSteerAngle();
	if(angle>0.01f)
		angle -= 0.01/2.f;
	else if(angle<-0.01f)
		angle += 0.01/2.f;
}

void CarGameObject::Render(ModelShaderProgram* modelShader)
{
	glm::mat4 model = glm::translate(physicsObject.GetPosition()) * glm::rotate(-(physicsObject.GetCarHeading() * 180.f / 3.14f - 90.f), glm::vec3(0,1,0));
	this->model->Render(modelShader, model);
}


void CarGameObject::SteerLeft()
{
	physicsObject.SteerLeft();
}

void CarGameObject::SteerRight()
{
	physicsObject.SteerRight();
}

void CarGameObject::Throttle()
{
	physicsObject.Throttle();
}

void CarGameObject::Break()
{
	physicsObject.Break();
}

void CarGameObject::SetPosition(glm::vec3 position)
{
	physicsObject.SetPosition(position);
}
