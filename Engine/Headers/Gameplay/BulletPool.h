#pragma once
#include "Bullet.h"
#include "Resources\StackAllocator.h"
#include "API.h"

class Engine;

class BulletPool 
{
public:
	ENGINE_API BulletPool(int size, BulletInfo info, Engine* instance);
	~BulletPool();
	ENGINE_API Bullet* Get();
	ENGINE_API void Update(float deltaTime);
	ENGINE_API void Draw(glm::mat4 viewProjection);
private:
	int _index = 0;
	int _size;
	Bullet* _bullets = nullptr;
	StackAllocator::Marker _marker;
	Engine* _engineInstance = nullptr;
};