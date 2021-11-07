#include "Gameplay\Camera\Camera.h"
#include <glm\gtx\transform.hpp>

void Camera::SetPosition(glm::vec3 position) 
{
	_worldPosition = position;
	_view = glm::lookAt(_worldPosition - glm::vec3(0, 0, 20), _worldPosition, glm::vec3(0, 1, 0));
}

glm::mat4 Camera::GetViewProjection() const 
{
	return  _projection * _view;
}