#ifndef Camera_h__
#define Camera_h__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


class Camera
{
protected:
	glm::vec3 mPosition;
	glm::vec3 mUp;
	glm::vec3 mRight;
	glm::vec3 mDirection;
	glm::mat4 mViewMatrix;
	glm::mat4 mProjectionMatrix;

	glm::vec3 mObjectPosition;

	double mAngleX, mAngleY;

public:
	Camera();
	
#pragma region Setters and Getters
	void setCameraDirection(glm::vec3 direction);
	glm::vec3 getCameraDirection();

	void setCameraPosition(glm::vec3 position);
	glm::vec3 getCameraPosition();

	void setObjectPosition(glm::vec3 position);
	glm::vec3 getObjectPosition();
	
	void setYawAngle(float angle);

	glm::mat4 GetViewMatrix();
	void SetPerspectiveProjection(float FOV, float aspectRatio, float near, float far);
	glm::mat4 GetProjectionMatrix();
#pragma endregion

	virtual void Reset(glm::vec3 &eye, glm::vec3 &center, glm::vec3  &up);
	virtual void UpdateViewMatrix();

#pragma region Rotations
	/// <summary>
	/// Rotates the axes (N, R) about the U-axis with the specified angle. This is equivalent to
	/// a left-turn.
	/// </summary>//y--->z--->x
	virtual void Yaw(float angleDegrees);

	/// <summary>
	/// Rotates the axes (U, N) about the R-axis with the specified angle. This is equivalent
	/// to a look-up (up turn).
	/// </summary>//x--->y--->z
	virtual void Pitch(float angleDegrees);

	/// <summary>
	/// Rotates the axes (R, U) about the N-axis with the specified angle.
	/// </summary>//z--->x--->y
	virtual void Roll(float angleDegrees);
#pragma endregion

#pragma region Translations

	/// <summary>
	/// Moves the eye point a distance dist forward == -dist * N
	/// Walk
	/// </summary>
	virtual void Walk(float dist);

	/// <summary>
	/// Moves the eye point a distance dist to the right == +dist * R
	/// Strafe
	/// </summary>
	virtual void Strafe(float dist);

	/// <summary>
	/// Moves the eye point a distance dist upward == +dist * U
	/// Fly
	/// </summary>
	virtual void Fly(float dist);

#pragma endregion

	virtual void Slide(float stepR, float stepU, float stepD);
};

#endif