#pragma once
#include "Actor.h"
#include "Physics\AABB.h"
#include "API.h"

struct BulletInfo 
{
	float damage;
};

class Bullet : public Actor 
{
public:
	Bullet(VisualComponent* visual, BulletInfo info);
	~Bullet();
	void Update(float deltaTime);
	void Draw(glm::mat4 viewProjection);
	ENGINE_API void SetActive(bool active) { _isActive = active; }
	ENGINE_API void SetPosition(glm::vec3 pos);
	ENGINE_API void SetVelocity(glm::vec2 vel);
	ENGINE_API float GetDamageValue() { return _info.damage; }
private:
	BulletInfo _info;
	AABB* _aabb;
	bool _isActive = false;
};