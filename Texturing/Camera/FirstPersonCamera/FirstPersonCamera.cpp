#include "FirstPersonCamera.h"

FirstPersonCamera::FirstPersonCamera(void)
{
}

FirstPersonCamera::FirstPersonCamera(glm::vec3 objectPosition) : Camera()
{
	Reset(objectPosition, objectPosition, glm::vec3(0, 1, 0));
}

void FirstPersonCamera::UpdateViewMatrix()
{
	mDirection = glm::vec3(
		-cos(mAngleY)*sin(mAngleX),
		sin(mAngleY),
		-cos(mAngleY)*cos(mAngleX));

	mDirection = glm::normalize(mDirection);

	mRight = glm::cross(mDirection, glm::vec3(0, 1, 0));

	mUp = glm::cross(mRight, mDirection);

	glm::vec3 center = mPosition + mDirection;
	mViewMatrix = glm::lookAt(mPosition, center, mUp);
}

void FirstPersonCamera::setCameraDirection(glm::vec3 direction)
{
	mDirection = direction;
}

glm::vec3 FirstPersonCamera::getCameraDirection()
{
	return mDirection;
}

void FirstPersonCamera::setCameraPosition(glm::vec3 position)
{
	mPosition = position;
}

glm::vec3 FirstPersonCamera::getCameraPosition()
{
	return mPosition;
}

#pragma region Rotations
void FirstPersonCamera::Yaw(float angleDegrees)
{
	mAngleX += angleDegrees;
}

void FirstPersonCamera::Pitch(float angleDegrees)
{
	mAngleY += angleDegrees;
}

void FirstPersonCamera::Roll(float angleDegrees)
{

}
#pragma endregion

#pragma region Translations
void FirstPersonCamera::Walk(float dist)
{
	mPosition += dist * mDirection;
}

void FirstPersonCamera::Strafe(float dist)
{
	mPosition += dist *mRight;
}

void FirstPersonCamera::Fly(float dist)
{
	mPosition += dist * mUp;
}
#pragma endregion

void FirstPersonCamera::Slide(float stepR, float stepU, float stepD)
{
	mPosition += stepR *mRight;
	mPosition += stepU * mUp;
	//next transition needs to be tested!!.
	mPosition += stepD * mDirection;
}