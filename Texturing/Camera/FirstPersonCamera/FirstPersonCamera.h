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

	void UpdateViewMatrix();

#pragma region Rotations
	/// <summary>
	/// Rotates the axes (N, R) about the U-axis with the specified angle. This is equivalent to
	/// a left-turn.
	/// </summary>//y--->z--->x
	void Yaw(float angleDegrees);

	/// <summary>
	/// Rotates the axes (U, N) about the R-axis with the specified angle. This is equivalent
	/// to a look-up (up turn).
	/// </summary>//x--->y--->z
	void Pitch(float angleDegrees);

	/// <summary>
	/// Rotates the axes (R, U) about the N-axis with the specified angle.
	/// </summary>//z--->x--->y
	void Roll(float angleDegrees);
#pragma endregion

};
#endif // FirstPersonCamera_h__

