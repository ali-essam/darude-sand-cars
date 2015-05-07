#include "CarPhysicsObject.h"

CarPhysicsObject::CarPhysicsObject():steerAngle(0.f), carHeading(3.14f/2.f), wheelBase(20.f),
	carSpeed(0.f), engineForce(0.00005f), breakForce(-0.0001f), maxCarSpeed(0.2f)
{
	velocity = carSpeed * glm::normalize(glm::vec3(cos(carHeading), 0.f, sin(carHeading)));
	ResetControls();
}

CarPhysicsObject::~CarPhysicsObject()
{
}

void CarPhysicsObject::Update(float dt)
{
	float force = 0.f;

	if(throttling)
	{
		force+= engineForce;
	}
	if(breaking)
	{
		force+= breakForce;
	}

	if(!throttling && !breaking && carSpeed > 0.f)
	{
		force = -0.000005f;
	}

	if(steeringRight)
	{
		steerAngle += 0.01 *dt;
		if(steerAngle > M_PI_4)
			steerAngle = M_PI_4;
	}
	if(steeringLeft)
	{
		steerAngle -= 0.01 *dt;
		if(steerAngle < -M_PI_4)
			steerAngle = -M_PI_4;
	}
	if(!steeringRight && !steeringLeft)
	{
		if(steerAngle > 0.f)
			steerAngle -= 0.01 *dt;
		else if(steerAngle < 0.f)
			steerAngle += 0.01 *dt;

		if(steerAngle > -0.1f && steerAngle < 0.1f)
			steerAngle = 0.f;
	}
	//force = 0.f;
	float acc = force / mass;

	carSpeed = sqrt(velocity.x*velocity.x + velocity.z*velocity.z) + acc*dt;
	if(carSpeed<0.01f && breaking)
	{
		carSpeed = 0.f;
		velocity = glm::vec3(0.f);
	}
	if(carSpeed > maxCarSpeed)
	{
		carSpeed = maxCarSpeed;
	}
	//printf("CarSpeed: (%.3f, %.3f)\n", velocity.x, velocity.z);
	
	glm::vec2 carLocation = glm::vec2(position.x, position.z);
	//printf("CarLocation: (%.3f, %.3f)\n", position.x, position.z);
	glm::vec2 frontWheel = carLocation + wheelBase/2 * glm::vec2( cos(carHeading) , sin(carHeading) );
	glm::vec2 backWheel = carLocation - wheelBase/2 * glm::vec2( cos(carHeading) , sin(carHeading) );


	backWheel += carSpeed * dt * glm::vec2(cos(carHeading) , sin(carHeading));
	frontWheel += carSpeed * dt * glm::vec2(cos(carHeading+steerAngle) , sin(carHeading+steerAngle));

	carLocation = (frontWheel + backWheel) / 2.f;
	carHeading = atan2( frontWheel.y - backWheel.y , frontWheel.x - backWheel.x );
	//printf("CarHeading: %.3f\n", carHeading);
	position = glm::vec3(carLocation.x, position.y, carLocation.y);

	velocity = carSpeed * glm::normalize(glm::vec3(cos(carHeading), 0.f, sin(carHeading)));

	boundingBox->SetCenter(position);

	ResetControls();
}


void CarPhysicsObject::SteerLeft()
{
	steeringLeft = true;
}

void CarPhysicsObject::SteerRight()
{
	steeringRight = true;
}

void CarPhysicsObject::Throttle()
{
	throttling = true;
}

void CarPhysicsObject::Break()
{
	breaking = true;
}

void CarPhysicsObject::ResetControls()
{
	steeringLeft = false;
	steeringRight = false;
	throttling = false;
	breaking = false;
}