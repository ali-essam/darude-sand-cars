#include "RigidBody.h"

RigidBody::RigidBody()
{
}

RigidBody::~RigidBody()
{
}

void RigidBody::Update(float dt)
{
	if(mass == 0.f) return;
	glm::vec3 acc = force / mass;
	velocity += acc * dt;
	// printf("v = %f %f %f\n",velocity[0], velocity[1], velocity[2]); 
	position += velocity * dt;
	boundingBox->SetCenter(position);
}

void RigidBody::AddForce(glm::vec3 f)
{
	this->force += f * 0.0000001f;
}

void RigidBody::RemoveForce(glm::vec3 f)
{
	this->force -= f * 0.0000001f;
}

void RigidBody::SetForce(glm::vec3 f)
{
	this->force = f * 0.0000001f;
}