#ifndef DirectionalLightSource_h__
#define DirectionalLightSource_h__

#include <glm\glm.hpp>

class DirectionalLightSource
{
	glm::vec3 direction;
	glm::vec3 color;

public:

	inline glm::vec3 GetDirection();
	inline glm::vec3 GetColor();
    
	inline void SetDirection(glm::vec3 _direction);
	inline void SetColor(glm::vec3 _color);

};

#endif // DirectionalLightSource_h__