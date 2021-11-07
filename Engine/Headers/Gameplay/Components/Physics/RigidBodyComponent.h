#pragma once
#include "..\Component.h"
#include "Physics\AbstractBounds.h"
#include "API.h"

class RigidBodyComponent 
{
public:
	RigidBodyComponent(Transform* transform, AbstractBounds* bounds) : _transform(transform), _bounds(bounds) {}
	ENGINE_API virtual void Init() {}
	ENGINE_API virtual void Update(float deltaTime);
	ENGINE_API void SetVelocity(glm::vec2 velocity);
	ENGINE_API virtual void Shutdown() {}
protected:
	AbstractBounds* _bounds = nullptr;
	Transform* _transform = nullptr;
	glm::vec2 _velocity = glm::vec2(0,0);
};