#pragma once
#include "Engine.h"
#include "Log.h"
#include "Plane.h"

class Part : public Actor
{
public:
    Part(Engine* engine, ActorHandle playerActorHandle) : Actor() {
        void* mem = engine->AllocMem(sizeof(AABB));
        _aabb = new (mem) AABB(this, glm::vec2(8.f, 8.f));
        mem = engine->AllocMem(sizeof(RigidBodyComponent));
        _rigidBody = new RigidBodyComponent(this, _aabb);
        _playerActorHandle = playerActorHandle;

        Texture texture("Assets/pixelshmup/tiles.png");

        mem = engine->AllocMem(sizeof(TileVisual));
        TileVisual* partVisual = new (mem) TileVisual();
        partVisual->SetSprite(18, texture, 16, 16);
        Scale(glm::vec3(1.f) * 8.f);

        _visuals = partVisual;
        _visuals->SetTransform(this);
        _visuals->Init();

        _engine = engine;

        texture.Free();
    }
    virtual void Update(float deltaTime) override
    {
        Actor* playerActor = _engine->GetActor(_playerActorHandle);
        Plane& plane = static_cast<Plane&>(*playerActor);
        AABB* planeAABB = plane.GetBoundingBox();

        if (_aabb->Intersect(*planeAABB) && plane.losePartCooldown <= 0.f)
        {
            Log::LogMessage("Part was picked up", "Gameplay");
            _engine->DestroyActor(this->_handle);
        }
    }
private:
    AABB* _aabb;
    Engine* _engine;
    ActorHandle _playerActorHandle;
};

