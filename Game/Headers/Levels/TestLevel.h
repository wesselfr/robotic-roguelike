#pragma once
#include "Gameplay\Level.h"
#include "Actors\Player.h"
#include "Commands.h"

#define SPAWN_ACTOR(ENGINE, ACTOR) ENGINE->SpawnActor(new (ENGINE->AllocMem(sizeof(ACTOR))) ACTOR(ENGINE))

class TestLevel : public Level {
    void OnBegin() override
    {
        _playerHandle = SPAWN_ACTOR(engine, Player);

        engine->SetPlayerActor(_playerHandle);
        Actor* playerActor = engine->GetActor(_playerHandle);
        playerActor->GetRigidBody()->SetVelocity(glm::vec2(0, 1));
        playerActor->Translate(glm::vec3(-512, 512, -20.f));
        playerActor->Scale(glm::vec3(1.f) * 32.f);

        engine->AddInputCommand(Button::KeyW, new MoveCommand(engine, {0,10}));
        engine->AddInputCommand(Button::KeyA, new MoveCommand(engine, {10,0}));
        engine->AddInputCommand(Button::KeyS, new MoveCommand(engine, {0, -10}));
        engine->AddInputCommand(Button::KeyD, new MoveCommand(engine, {-10,0}));
        
        const EngineConfiguration& config = engine->GetConfig();
        // Only initialize text rendering when not running headless.
        if (!config.isHeadless) {
            _text.Init();
            _text.SetProjection(glm::ortho(0.0f, static_cast<float>(config.width), 0.0f, static_cast<float>(config.height)));
        }
    }
    void Update(float deltaTime) override
    {
        if (!engine->GetConfig().isHeadless) {
            Actor* planeActor = engine->GetActor(_playerHandle);
            glm::vec3 planeWorldPosition = planeActor->GetWorldPosition();
            _text.Draw("Plane", glm::vec2(-planeWorldPosition.x - 25.f, planeWorldPosition.y + 35.f), 0.4f, glm::vec3(1.f));

        }
    }
    void OnShutdown() override
    {
        
    }
private:
    Text _text;
    ActorHandle _playerHandle;
};

