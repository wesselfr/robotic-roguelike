#pragma once
#include "Engine.h"
#include "Gameplay\Actor.h"
#include "Gameplay\Components\TileVisual.h"

class Plane : public Actor
{
public:
    Plane(Engine* engine) : Actor() {
        void* mem = engine->AllocMem(sizeof(AABB));
        _aabb = new (mem) AABB(this, glm::vec2(32, 32));
        mem = engine->AllocMem(sizeof(RigidBodyComponent));
        _rigidBody = new (mem) RigidBodyComponent(this, _aabb);

        if (!engine->GetConfig().isHeadless) {
            Texture texture("Assets/Textures/pixelshmup/ships.png");

            mem = engine->AllocMem(sizeof(TileVisual));
            TileVisual* planeVisual = new (mem) TileVisual();
            planeVisual->SetSprite(5, texture);

            _visuals = planeVisual;
            _visuals->SetTransform(this);
            _visuals->Init();
            
            texture.Free();
        }
    }
    virtual void Update(float deltaTime) override
    {
        if (speed > 300.f) {
            speed = 300.f;
        }

        speed -= speed * (0.1f * deltaTime);

        if (speed < 50.0f) { speed = 50.f; }

        LookAt(GetWorldPosition() + glm::vec3(direction.y, -direction.x, 0));
        _rigidBody->SetVelocity(direction * speed);
        _rigidBody->Update(deltaTime);

        losePartCooldown -= deltaTime;
        if (losePartCooldown < 0.f) { losePartCooldown = 0.0f; }
    }
    AABB* GetBoundingBox() { return _aabb; }
    glm::vec2 direction = glm::vec2(1, 0);
    float speed = 50.f;
    float angle = 0.f;
    float losePartCooldown = 0.f;
private:
    AABB* _aabb;
};

