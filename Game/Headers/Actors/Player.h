#pragma once
#include "Engine.h"
#include "Gameplay/Actor.h"

class Player : public Actor
{
public:
	Player(Engine* engine);
	void Update(float deltaTime) override;
private:
	AABB* _aabb;
};
