#include "Gameplay\BulletPool.h"
#include "Engine.h"

BulletPool::BulletPool(int size, BulletInfo info, Engine* instance)
{
	_engineInstance = instance;

	_size = size;
	Bullet* bulletMem = static_cast<Bullet*>(instance->AllocMem(sizeof(Bullet) * _size));
	QuadVisual* visualMem = static_cast<QuadVisual*>(instance->AllocMem(sizeof(QuadVisual) * _size));
	_marker = (uint64_t)bulletMem;

	// Only initialize visuals when engine is not running headless.
	if (!instance->GetConfig().isHeadless) {
		for (int i = 0; i < _size; i++)
		{
			new (&visualMem[i]) QuadVisual();
		}
	}
	else {
		// Otherwise, free the memory that was allocated for visuals.
		instance->FreeToMarker((uint64_t)bulletMem);
	}

	// Initialize bullets
	for (int i = 0; i < _size; i++) 
	{
		// Initialize a bullet based on the given memory address.
		if (!instance->GetConfig().isHeadless) {
			new (&bulletMem[i]) Bullet(&visualMem[i], info);
		}
		else {
			new (&bulletMem[i]) Bullet(new NullVisual(), info);
		}
	}

	_bullets = bulletMem;
}

BulletPool::~BulletPool() 
{
	// Call destructor and remove memory block.
	for (int i = 0; i < _size; i++) 
	{
		_bullets[i].~Bullet();
	}
	_engineInstance->FreeToMarker(_marker);
}

Bullet* BulletPool::Get() 
{
	_index++;
	if (_index >= _size) 
	{
		_index = 0;
	}
	return &_bullets[_index];
}

void BulletPool::Update(float deltaTime) 
{
	for (int i = 0; i < _size; i++) 
	{
		_bullets[i].Update(deltaTime);
	}
}

void BulletPool::Draw(glm::mat4 viewProjection) 
{
	for (int i = 0; i < _size; i++)
	{
		_bullets[i].Draw(viewProjection);
	}
}