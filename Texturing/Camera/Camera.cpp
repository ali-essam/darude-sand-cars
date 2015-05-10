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

glm::mat4 Camera::GetViewMatrix()
{
	return mViewMatrix;
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

void Camera::UpdateViewMatrix()
{

}