#ifndef ThirdPersonCamera_h__
#define ThirdPersonCamera_h__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <memory>
#include "Camera\Camera.h"

//Note: this camera assumes left hand rule.
class ThirdPersonCamera : public Camera
{
	float distanceFromObject;
	float distanceOnY;

	void updateCameraPositionAndDirection();
public:
	ThirdPersonCamera(void);
	ThirdPersonCamera(glm::vec3 cameraPosition, glm::vec3 objectPosition);

	void UpdateViewMatrix();
	void Reset(glm::vec3 &eye, glm::vec3 &center, glm::vec3  &up);
};
#endif