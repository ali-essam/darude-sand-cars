#include "CarPhysicsObject.h"

CarPhysicsObject::CarPhysicsObject():steerAngle(0.f), carHeading(3.14f/2.f), wheelBase(20.f), carSpeed(0.2f)
{
	velocity = carSpeed * glm::normalize(glm::vec3(cos(carHeading), 0.f, sin(carHeading)));
}

CarPhysicsObject::~CarPhysicsObject()
{
}

void CarPhysicsObject::Update(float dt)
{
	glm::vec2 carLocation = glm::vec2(position.x, position.z);
	//printf("CarLocation: (%.3f, %.3f)\n", position.x, position.z);
	glm::vec2 frontWheel = carLocation + wheelBase/2 * glm::vec2( cos(carHeading) , sin(carHeading) );
	glm::vec2 backWheel = carLocation - wheelBase/2 * glm::vec2( cos(carHeading) , sin(carHeading) );
	
	carSpeed = sqrt(velocity.x*velocity.x + velocity.z*velocity.z);
	//printf("CarSpeed: (%.3f, %.3f)\n", velocity.x, velocity.z);

	backWheel += carSpeed * dt * glm::vec2(cos(carHeading) , sin(carHeading));
	frontWheel += carSpeed * dt * glm::vec2(cos(carHeading+steerAngle) , sin(carHeading+steerAngle));

	carLocation = (frontWheel + backWheel) / 2.f;
	carHeading = atan2( frontWheel.y - backWheel.y , frontWheel.x - backWheel.x );
	//printf("CarHeading: %.3f\n", carHeading);
	position = glm::vec3(carLocation.x, position.y, carLocation.y);
	
	velocity = carSpeed * glm::normalize(glm::vec3(cos(carHeading), 0.f, sin(carHeading)));

	boundingBox->SetCenter(position);
}
