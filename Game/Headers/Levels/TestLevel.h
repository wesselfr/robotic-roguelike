#pragma once
#include "Gameplay\Level.h"
#include "Actors\Plane.h"
#include "Commands.h"

#define SPAWN_ACTOR(ENGINE, ACTOR) ENGINE->SpawnActor(new (ENGINE->AllocMem(sizeof(ACTOR))) ACTOR(ENGINE))

class TestLevel : public Level {
    void OnBegin() override
    {
        _playerHandle = SPAWN_ACTOR(engine, Plane);

        engine->SetPlayerActor(_playerHandle);
        Actor* playerActor = engine->GetActor(_playerHandle);
        playerActor->GetRigidBody()->SetVelocity(glm::vec2(0, 1));
        playerActor->Translate(glm::vec3(-512, 512, -20.f));
        playerActor->Scale(glm::vec3(1.f) * 32.f);

        SPAWN_ACTOR(engine, Plane);

        BulletInfo bulletInfo;
        bulletInfo.damage = 20;
        _pool = new BulletPool(100, bulletInfo, engine);

        engine->AddInputCommand(Button::KeyQ, new SpawnPartCommand(engine, _playerHandle));
        engine->AddInputCommand(Button::KeyW, new ChangeSpeedCommand(engine, 30.f));
        engine->AddInputCommand(Button::KeyS, new ChangeSpeedCommand(engine, -20.f));
        engine->AddInputCommand(Button::KeyA, new RotateCommand(engine, -3.f));
        engine->AddInputCommand(Button::KeyD, new RotateCommand(engine, 3.f));
        engine->AddInputCommand(Button::KeySpace, new ShootCommand(engine, _pool));
        
        const EngineConfiguration& config = engine->GetConfig();
        // Only initialize text rendering when not running headless.
        if (!config.isHeadless) {
            _text.Init();
            _text.SetProjection(glm::ortho(0.0f, static_cast<float>(config.width), 0.0f, static_cast<float>(config.height)));
        }
    }
    void Update(float deltaTime) override
    {
        //RotateCommand rotate(engine, 3.f);
        //rotate.Execute(*engine->GetActor(1));

        _pool->Update(deltaTime);

        if (!engine->GetConfig().isHeadless) {
            Actor* planeActor = engine->GetActor(_playerHandle);
            glm::vec3 planeWorldPosition = planeActor->GetWorldPosition();
            _text.Draw("Plane", glm::vec2(-planeWorldPosition.x - 25.f, planeWorldPosition.y + 35.f), 0.4f, glm::vec3(1.f));

            _pool->Draw(engine->GetActiveCamera()->GetViewProjection());
        }
    }
    void OnShutdown() override
    {
        
    }
private:
    Text _text;
    ActorHandle _playerHandle;
    BulletPool* _pool;
};

