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

	double mAngleX, mAngleY;
	virtual void Reset(glm::vec3 &eye, glm::vec3 &center, glm::vec3  &up);

public:
	Camera();
	
#pragma region Setters and Getters
	glm::mat4 GetViewMatrix();
	void SetPerspectiveProjection(float FOV, float aspectRatio, float near, float far);
	glm::mat4 GetProjectionMatrix();
#pragma endregion

	virtual void UpdateViewMatrix();
};

#endif