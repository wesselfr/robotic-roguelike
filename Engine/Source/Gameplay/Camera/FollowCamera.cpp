#include "Gameplay\Camera\FollowCamera.h"
#include "MathUtils.h"

void FollowCamera::SetTarget(Transform* target) 
{
	assert(target != nullptr);
	_target = target;
}

void FollowCamera::Update(float deltaTime) 
{
	glm::vec3 targetPos = _target->GetWorldPosition();
	glm::vec3 pos = Lerp(_worldPosition, _target->GetWorldPosition(), _followSpeed * deltaTime);
	SetPosition(pos);
}

void FollowCamera::SetFollowSpeed(float speed) 
{
	_followSpeed = speed;
}