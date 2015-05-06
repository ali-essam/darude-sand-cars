#include "PhysicsObject.h"

PhysicsObject::PhysicsObject():mass(1.f), position(glm::vec3(0.f)), velocity(glm::vec3(0.f))
{
	boundingBox = new AABoundingBox(position, glm::vec3(0,0,0));
}

PhysicsObject::PhysicsObject(AABoundingBox* boundingBox):mass(1.f), position(glm::vec3(0.f)), velocity(glm::vec3(0.f))
{
	this->SetBoundingBox(boundingBox);
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