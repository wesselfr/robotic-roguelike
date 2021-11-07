#include "Gameplay\Bullet.h"

Bullet::Bullet(VisualComponent* visual, BulletInfo info) : Actor(visual) 
{
	_info = info;
	_aabb = new AABB(this, glm::vec2(1, 1));
	_rigidBody = new RigidBodyComponent(this, _aabb);
	Scale(glm::vec3(10.f));
}

Bullet::~Bullet() 
{
	delete _aabb;
	delete _rigidBody;
}

void Bullet::Update(float deltaTime)
{
	if (_isActive) {
		_rigidBody->Update(deltaTime);
	}
}

void Bullet::Draw(glm::mat4 viewProjection) 
{
	if (_isActive) 
	{
		_visuals->Draw(viewProjection);
	}
}

void Bullet::SetPosition(glm::vec3 position) 
{
	_worldPosition = position;
}

void Bullet::SetVelocity(glm::vec2 velocity) 
{
	assert(_rigidBody != nullptr && "Cannot set velocity without rigidbody.");
	_rigidBody->SetVelocity(velocity);
}