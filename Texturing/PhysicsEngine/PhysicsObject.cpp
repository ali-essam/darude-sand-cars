#include "PhysicsObject.h"

PhysicsObject::PhysicsObject()
{
}

PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::SetPosition(glm::vec3 position)
{
	this->position = position;
	boundingBox->SetCenter(position);
}

void PhysicsObject::SetVelocity(glm::vec3 velocity)
{
	this->velocity = velocity;
}

void PhysicsObject::SetMass(float mass)
{
	this->mass = mass;
}


void PhysicsObject::SetBoundingBox(AABoundingBox* boundingBox)
{
	this->boundingBox = boundingBox;
}



void PhysicsObject::Translate(glm::vec3 dist)
{
	this->position += dist;
	boundingBox->SetCenter(position);
}