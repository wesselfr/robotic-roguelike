#include "Gameplay\Transform.h"
#include<glm\glm.hpp>
#include<glm\gtx\transform.hpp>

void Transform::Translate(glm::vec3 translation)
{
	_worldPosition += translation;
}

void Transform::Scale(glm::vec3 scale)
{
	_scale = scale;
}

void Transform::LookAt(glm::vec3 pos)
{
	glm::vec3 relative = pos - _worldPosition;
	float angle = atan2f(relative.y, relative.x);
	_rotation = glm::mat4(1);
	_rotation = glm::rotate(_rotation, angle, glm::vec3(0, 0, 1));
}

const glm::vec3& Transform::GetWorldPosition() 
{
	return _worldPosition; 
}

void Transform::SetWorldPosition(glm::vec3 worldPos) 
{
	_worldPosition = worldPos;
}

glm::mat4 Transform::GetModelMatrix()
{
	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, _worldPosition);
	model = glm::scale(model, _scale);
	model *= _rotation;
	return model;
}