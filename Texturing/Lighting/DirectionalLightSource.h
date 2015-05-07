#ifndef DirectionalLightSource_h__
#define DirectionalLightSource_h__

#include <glm\glm.hpp>

class DirectionalLightSource
{
	glm::vec3 direction;
	glm::vec3 color;

public:
	DirectionalLightSource::DirectionalLightSource();
	DirectionalLightSource::DirectionalLightSource(glm::vec3 direction, glm::vec3 color);


	glm::vec3 GetDirection();
	glm::vec3 GetColor();
    
	void SetDirection(glm::vec3 _direction);
	void SetColor(glm::vec3 _color);
};

#endif // DirectionalLightSource_h__