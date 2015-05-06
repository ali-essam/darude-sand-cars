#include "DirectionalLightSource.h"

glm::vec3 DirectionalLightSource::GetDirection()
{
	return direction;
}

glm::vec3 DirectionalLightSource::GetColor()
{
	return color;
}

void DirectionalLightSource::SetColor(glm::vec3 _color)
{
	color=_color;
}

void DirectionalLightSource::SetDirection(glm::vec3 _direction)
{
	direction=_direction;
}
