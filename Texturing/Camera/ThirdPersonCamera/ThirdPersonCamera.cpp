#include "ThirdPersonCamera.h"

ThirdPersonCamera::ThirdPersonCamera(void)
{
}


ThirdPersonCamera::ThirdPersonCamera(glm::vec3 cameraPosition, glm::vec3 objectPosition) : Camera()
{
	this->Reset(cameraPosition, objectPosition, glm::vec3(0, 1, 0));
}

void ThirdPersonCamera::Reset(glm::vec3 &eye, glm::vec3 &center, glm::vec3 &up)
{
	mObjectPosition = center;
	distanceOnY = abs(eye.y - center.y);
	distanceFromObject = sqrt(abs(eye.x - center.x)*abs(eye.x - center.x) + abs(eye.y - center.y)*abs(eye.y - center.y) + abs(eye.z - center.z)*abs(eye.z - center.z));
	Camera::Reset(eye, center, up);
}

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

void ThirdPersonCamera::setCameraHeight(float height)
{
	distanceOnY = height;
}

float ThirdPersonCamera::getCameraHeight()
{
	return distanceOnY;
}