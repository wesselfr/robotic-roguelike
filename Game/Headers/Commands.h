#pragma once
#include "Engine.h"
#include "Log.h"
#include "Gameplay\Command.h"
#include "Gameplay\BulletPool.h"
#include "Actors\Plane.h"
#include "Actors\Part.h"

class RotateCommand : public Command
{
public:
    RotateCommand(Engine* engine, float rotationSpeed) { _engine = engine; _rotationSpeed = rotationSpeed; }
    virtual void Execute(Actor& actor) override
    {
        Plane& plane = static_cast<Plane&>(actor);
        plane.angle += _rotationSpeed * _engine->GetDeltaTime();
        plane.direction = glm::vec2(cos(plane.angle), sin(plane.angle));
    }
private:
    Engine* _engine = nullptr;
    float _rotationSpeed;
};

class ChangeSpeedCommand : public Command {
public:
    ChangeSpeedCommand(Engine* engine, float speedDelta) { _engine = engine; _speedDelta = speedDelta; }
    virtual void Execute(Actor& actor) override
    {
        Plane& plane = static_cast<Plane&>(actor);
        plane.speed += _speedDelta * _engine->GetDeltaTime();
    }
private:
    Engine* _engine = nullptr;
    float _speedDelta = 0.0f;
};

class ShootCommand : public Command
{
public:
    ShootCommand(Engine* engine, BulletPool* bullets)
    {
        _engine = engine;
        _bullets = bullets;
    }
    virtual void Execute(Actor& actor) override
    {
        Bullet* bullet = _bullets->Get();
        Plane& plane = static_cast<Plane&>(actor);
        bullet->SetPosition(actor.GetWorldPosition());
        bullet->SetActive(true);
        glm::vec2 direction = glm::vec2(cos(plane.angle), sin(plane.angle));
        bullet->SetVelocity(direction * (plane.speed + 100.f));
        bullet->LookAt(actor.GetWorldPosition() + glm::vec3(direction, 0));
    }
private:
    Engine* _engine = nullptr;
    BulletPool* _bullets;
};

class SpawnPartCommand : public Command
{
public:
    SpawnPartCommand(Engine* engine, ActorHandle playerHandle)
    {
        _engine = engine;
        _playerHandle = playerHandle;
    }
    virtual void Execute(Actor& actor) override
    {
        Plane& plane = static_cast<Plane&>(actor);
        if (plane.losePartCooldown <= 0.f) {
            const ActorHandle& handle = _engine->SpawnActor(new Part(_engine, _playerHandle));
            Actor* spawnedActor = _engine->GetActor(handle);
            spawnedActor->Translate(actor.GetWorldPosition());

            Log::LogMessage("Part has been lost from plane.", "Gameplay");
            plane.losePartCooldown = 5.f;
        }
    }
private:
    Engine* _engine = nullptr;
    ActorHandle _playerHandle;
};

