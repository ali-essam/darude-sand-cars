#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Initialize()
{
	//this->physicsObject.position = glm::vec3(0, 30, -50);
	this->boundingBox.SetCenter(this->physicsObject.GetPosition());
	this->boundingBox.SetSize(AABoundingBox::CalculateBoundingBoxSize(model->GetAllVerticies()));
	this->physicsObject.SetBoundingBox(&boundingBox);
}

void GameObject::Update(double dt)
{
	
}

void GameObject::Render(GraphicsDevice* graphicsDevice)
{
	glm::mat4 model = glm::translate(physicsObject.GetPosition());//* glm::scale(0.01f, 0.01f, 0.01f);
	this->model->Render(graphicsDevice, model);
}