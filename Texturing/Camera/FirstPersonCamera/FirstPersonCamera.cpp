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
	mPosition = mObjectPosition;
	
	mDirection = glm::vec3(
		-cos(mAngleY)*sin(mAngleX),
		sin(mAngleY),
		-cos(mAngleY)*cos(mAngleX));

	mDirection = glm::normalize(mDirection);

	mRight = glm::cross(mDirection, glm::vec3(0, 1, 0));

	mUp = glm::cross(mRight, mDirection);

	glm::vec3 center = mPosition + mDirection;
	mViewMatrix = glm::lookAt(mPosition, center, mUp);

	//glm::mat4 view = glm::mat4(	mRight.x,		mRight.y,		mRight.z,		-glm::dot(mPosition,mRight),
	//	mUp.x,			mUp.y,			mUp.z,			-glm::dot(mPosition,mUp),
	//	mDirection.x,	mDirection.y,	mDirection.z,	-glm::dot(mPosition,mDirection),
	//	0,				0,				0,				1);
	//mViewMatrix = glm::transpose(view);
}

void FirstPersonCamera::Yaw(float angleDegrees)
{
	mAngleX += angleDegrees;
}

void FirstPersonCamera::Pitch(float angleDegrees)
{
	double PI = 3.14;
	if (mAngleY + angleDegrees < PI / 2.0 && mAngleY + angleDegrees > -PI / 2.0)
		mAngleY += angleDegrees;
}

void FirstPersonCamera::Roll(float angleDegrees)
{
	//no ROLL!!!
}