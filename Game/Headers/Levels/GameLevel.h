#pragma once
#include "Gameplay\Level.h"
#include "Actors\Player.h"
#include "Commands.h"

#define SPAWN_ACTOR(ENGINE, ACTOR) ENGINE->SpawnActor(new (ENGINE->AllocMem(sizeof(ACTOR))) ACTOR(ENGINE))

class GameLevel : public Level {
public:
    void OnBegin() override
    {
		_player = SPAWN_ACTOR(engine, Player);
        engine->SetPlayerActor(_player);

        glm::vec3 playerPos = {engine->GetConfig().width * -0.5f, engine->GetConfig().height * 0.15f, -20};
        engine->GetActor(_player)->SetWorldPosition(playerPos);
        engine->GetActor(_player)->Scale(glm::vec3(1) * 32.f);

        BulletInfo bulletInfo;
        bulletInfo.damage = 20;
        bulletInfo.visual = TileVisual(0,"Assets/Textures/pixelshmup/tiles.png", 16, 16);
        _bullets = new BulletPool(100, bulletInfo, engine);

        engine->AddInputCommand(Button::KeyA, new MoveCommand(engine, {1,0},350.f));
        engine->AddInputCommand(Button::KeyD, new MoveCommand(engine,{-1,0},350.f));
        engine->AddInputCommand(Button::KeySpace, new ShootCommand(engine, _bullets));

        // Score
        _scoreText.Init();
		_scoreText.SetProjection(glm::ortho(0.0f, static_cast<float>(engine->GetConfig().width), 0.0f, static_cast<float>(engine->GetConfig().height)));
    }
    void Update(float deltaTime) override
    {
        _bullets->Update(deltaTime);
        _bullets->Draw(engine->GetActiveCamera()->GetViewProjection());

        Actor* playerActor = engine->GetActor(_player);
        EngineConfiguration config = engine->GetConfig();
        glm::vec3 playerPosition = playerActor->GetWorldPosition();

        if(playerPosition.x < -config.width){playerPosition.x = -config.width;}
        if(playerPosition.x > 0){playerPosition.x = 0;}
        playerActor->SetWorldPosition(playerPosition);

		_score += 3.6f * deltaTime;
        int score = static_cast<int>(_score);
        char buff[512];
        snprintf(buff,sizeof(char)*512, "Score: %i", score);
        _scoreText.Draw(buff, {engine->GetConfig().width * 0.35f, engine->GetConfig().height * 0.9f,}, 1.f, {1,1,1});

    }
    void OnShutdown() override
    {
        
    }
private:
    ActorHandle _player;
    BulletPool* _bullets;
	float _score = 0.f;
    Text _scoreText;

};

