#ifndef FirstPersonCamera_h__
#define FirstPersonCamera_h__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Camera\Camera.h"

//Note: this camera assumes left hand rule.
class FirstPersonCamera : public Camera
{
public:
	FirstPersonCamera(void);
	FirstPersonCamera(glm::vec3 objectPosition);

	void setCameraDirection(glm::vec3 direction);
	glm::vec3 getCameraDirection();

	void setCameraPosition(glm::vec3 position);
	glm::vec3 getCameraPosition();

	void UpdateViewMatrix();


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
#endif // FirstPersonCamera_h__

