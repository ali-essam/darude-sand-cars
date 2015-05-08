#include "Camera.h"

Camera::Camera(void)
{
	mAngleX = 0;
	mAngleY = 0;

	SetPerspectiveProjection(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}

void Camera::Reset(glm::vec3 &eye, glm::vec3 &center, glm::vec3 &up)
{
	mPosition = eye;

	//still needs normalization
	mDirection = center - mPosition;
	//i = j x k
	mRight = glm::cross(mDirection, up);
	//j = k x i
	mUp = up;
	//normalize all
	mUp = glm::normalize(mUp);
	mRight = glm::normalize(mRight);
	mDirection = glm::normalize(mDirection);

	mViewMatrix = glm::lookAt(mPosition, center, mUp);
}

#pragma region Setters and Getters
void Camera::setCameraDirection(glm::vec3 direction)
{
	mDirection = direction;
}

glm::vec3 Camera::getCameraDirection()
{
	return mDirection;
}

void Camera::setCameraPosition(glm::vec3 position)
{
	mPosition = position;
}

glm::vec3 Camera::getCameraPosition()
{
	return mPosition;
}

void Camera::setYawAngle(float angle)
{
	mAngleX = angle;
}

glm::mat4 Camera::GetViewMatrix()
{
	return mViewMatrix;
}

void Camera::setObjectPosition(glm::vec3 position)
{
	mObjectPosition = position;
}

glm::vec3 Camera::getObjectPosition()
{
	return mObjectPosition;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return mProjectionMatrix;
}

void Camera::SetPerspectiveProjection(float FOV, float aspectRatio, float near, float far)
{
	mProjectionMatrix = glm::perspective(FOV, aspectRatio, near, far);
}

#pragma endregion

#pragma region Rotations
void Camera::Yaw(float angleDegrees)
{
	mAngleX += angleDegrees;
}

void Camera::Pitch(float angleDegrees)
{
	mAngleY += angleDegrees;
}

void Camera::Roll(float angleDegrees)
{
	
}
#pragma endregion

#pragma region Translations
void Camera::Walk(float dist)
{
	mPosition += dist * mDirection;
}

void Camera::Strafe(float dist)
{
	mPosition += dist *mRight;
}

void Camera::Fly(float dist)
{
	mPosition += dist * mUp;
}
#pragma endregion

void Camera::Slide(float stepR, float stepU, float stepD)
{
	mPosition += stepR *mRight;
	mPosition += stepU * mUp;
	//next transition needs to be tested!!.
	mPosition += stepD * mDirection;
}

void Camera::UpdateViewMatrix()
{

}