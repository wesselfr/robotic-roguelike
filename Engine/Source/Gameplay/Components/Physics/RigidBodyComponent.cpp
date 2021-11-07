#include "Gameplay\Components\Physics\RigidBodyComponent.h"

void RigidBodyComponent::Update(float deltaTime) 
{
	_transform->Translate(glm::vec3(_velocity.x, _velocity.y, 0) * deltaTime);
}

void RigidBodyComponent::SetVelocity(glm::vec2 velocity) 
{
	_velocity = velocity;
}