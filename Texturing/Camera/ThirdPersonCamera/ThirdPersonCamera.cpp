#include "ThirdPersonCamera.h"

ThirdPersonCamera::ThirdPersonCamera(void)
{
	this->distanceFromObject = 5;
	this->distanceOnY = 2;
	glm::vec3 cameraPosition(0, distanceOnY, distanceFromObject);
	Camera::Reset(cameraPosition, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

ThirdPersonCamera::ThirdPersonCamera(glm::vec3 objectPosition) : Camera()
{
	this->distanceFromObject = 5;
	this->distanceOnY = 2;
	glm::vec3 cameraPosition(0, distanceOnY, distanceFromObject);
	Camera::Reset(cameraPosition, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

ThirdPersonCamera::ThirdPersonCamera(glm::vec3 objectPosition, float distanceFromObject, float cameraHeight) : Camera()
{
	this->distanceFromObject = distanceFromObject;
	this->distanceOnY = cameraHeight;
	glm::vec3 cameraPosition(0, cameraHeight, distanceFromObject);
	Camera::Reset(cameraPosition, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}
//
//void ThirdPersonCamera::Reset(glm::vec3 &eye, glm::vec3 &center, glm::vec3 &up)
//{
//	mObjectPosition = center;
//	distanceOnY = abs(eye.y - center.y);
//	distanceFromObject = sqrt(abs(eye.x - center.x)*abs(eye.x - center.x) + abs(eye.y - center.y)*abs(eye.y - center.y) + abs(eye.z - center.z)*abs(eye.z - center.z));
//	Camera::Reset(eye, center, up);
//}

void ThirdPersonCamera::updateCameraPositionAndDirection()
{
	float distanceOnX = distanceFromObject * sin(mAngleX);
	float distanceOnZ = distanceFromObject * cos(mAngleX);
	
	glm::vec3 displacement(distanceOnX, distanceOnY, distanceOnZ);

	mPosition = mObjectPosition + displacement;
	
	mDirection = mObjectPosition - mPosition;
	mDirection = glm::normalize(mDirection);
}

void ThirdPersonCamera::UpdateViewMatrix()
{
	updateCameraPositionAndDirection();
	
	mRight = glm::cross(mDirection, glm::vec3(0, 1, 0));
	mUp = glm::cross(mRight, mDirection);

	mRight = glm::normalize(mRight);
	mUp = glm::normalize(mUp);

	mViewMatrix = glm::lookAt(mPosition, mObjectPosition, mUp);
}
void ThirdPersonCamera::setCameraDirection(glm::vec3 direction)
{
	mDirection = direction;
}

glm::vec3 ThirdPersonCamera::getCameraDirection()
{
	return mDirection;
}

void ThirdPersonCamera::setCameraPosition(glm::vec3 position)
{
	mPosition = position;
}

void ThirdPersonCamera::setObjectPosition(glm::vec3 position)
{
	mObjectPosition = position;
}

glm::vec3 ThirdPersonCamera::getObjectPosition()
{
	return mObjectPosition;
}

glm::vec3 ThirdPersonCamera::getCameraPosition()
{
	return mPosition;
}

void ThirdPersonCamera::setCameraHeight(float height)
{
	distanceOnY = height;
}

float ThirdPersonCamera::getCameraHeight()
{
	return distanceOnY;
}

void ThirdPersonCamera::setCameraDistance(float distance)
{
	distanceFromObject = distance;
}

void ThirdPersonCamera::setYawAngle(float angle)
{
	mAngleX = angle;
}

float ThirdPersonCamera::getYawAngle()
{
	return mAngleX;
}

float ThirdPersonCamera::getCameraDistance()
{
	return distanceFromObject;
}

void ThirdPersonCamera::Yaw(float angleDegrees)
{
	mAngleX += angleDegrees;
}