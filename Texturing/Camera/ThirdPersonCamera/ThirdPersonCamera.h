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
	glm::vec3 mObjectPosition;

	float distanceFromObject;
	float distanceOnY;

	void updateCameraPositionAndDirection();

public:
	ThirdPersonCamera(void);
	ThirdPersonCamera(glm::vec3 objectPosition);
	ThirdPersonCamera(glm::vec3 objectPosition, float distanceFromObject, float cameraHeight);

	void UpdateViewMatrix();

	void setCameraDirection(glm::vec3 direction);
	glm::vec3 getCameraDirection();

	void setCameraPosition(glm::vec3 position);
	glm::vec3 getCameraPosition();

	void setObjectPosition(glm::vec3 position);
	glm::vec3 getObjectPosition();

	void setYawAngle(float angle);
	float getYawAngle();

	void setCameraHeight(float height);
	float getCameraHeight();

	void setCameraDistance(float distance);
	float getCameraDistance();

	void Yaw(float angleDegrees);
};
#endif