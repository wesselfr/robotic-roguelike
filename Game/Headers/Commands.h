#pragma once
#include "Engine.h"
#include "Log.h"
#include "Gameplay\Command.h"
#include "Gameplay\BulletPool.h"
#include "Actors\Player.h"
#include <random>

class MoveCommand : public Command
{
public:
	MoveCommand(Engine* engine, glm::vec2 direction, float speed = 1.f){_engine = engine; _direction = direction; _speed = speed;}
	void Execute(Actor& actor) override
	{
		glm::vec3 newPos = glm::vec3(_direction.x, _direction.y, 0);
		newPos *= _engine->GetDeltaTime() * _speed;
		newPos += actor.GetWorldPosition();
		actor.SetWorldPosition(newPos);
	}
private:
	Engine* _engine;
    glm::vec2 _direction;
	float _speed;
};

class ShootCommand : public Command
{
public:
	ShootCommand(Engine* engine, BulletPool* bullets, bool& canShoot) : _canShoot(canShoot)
	{
		_engine = engine;
		_bullets = bullets;
	}
	void Execute(Actor& actor) override
	{
		if(!_canShoot){return;}

		Log::LogMessage("Shoot!");
		glm::vec3 worldPosition = actor.GetWorldPosition();
		Bullet* bullet = _bullets->Get();
		bullet->SetWorldPosition(worldPosition);

		// Random spread.
		float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		r = -1 + r * (2);

		glm::vec2 direction = glm::vec2({r * 100.f, 700.f});
		bullet->SetVelocity(direction);
		bullet->LookAt(worldPosition + glm::vec3(direction.y, -direction.x, 0.f));
		bullet->SetActive(true);
		_canShoot = false;
	}
private:
	Engine* _engine;
	BulletPool* _bullets;
	bool& _canShoot;
};
