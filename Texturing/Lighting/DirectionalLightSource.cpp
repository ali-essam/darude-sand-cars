#include "DirectionalLightSource.h"

DirectionalLightSource::DirectionalLightSource()
{

}

DirectionalLightSource::DirectionalLightSource(glm::vec3 direction, glm::vec3 color):color(color)
{
	this->SetDirection(direction);
}

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
	_direction = glm::normalize(_direction);
	direction=_direction;
}
