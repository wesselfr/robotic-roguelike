#pragma once
#include "Camera.h"
#include "Gameplay\Transform.h"
#include "API.h"

class FollowCamera : public Camera 
{
public:
	FollowCamera(Transform* target, int width, int height) : Camera(glm::vec3(0,0,0), width, height) 
	{
		assert(target != nullptr && "Target cannot be nullptr");
		SetTarget(target);
		SetPosition(target->GetWorldPosition());
	}

	ENGINE_API virtual void Update(float deltaTime);
	ENGINE_API void SetTarget(Transform* target);
	ENGINE_API void SetFollowSpeed(float speed);
private:
	Transform* _target;
	float _followSpeed = 3.5f;
};