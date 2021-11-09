#pragma once
#include "Engine.h"
#include "Log.h"
#include "Gameplay\Command.h"
#include "Gameplay\BulletPool.h"
#include "Actors\Player.h"

class MoveCommand : public Command
{
public:
	MoveCommand(Engine* engine, glm::vec2 direction){_engine = engine; _direction = direction;}
	void Execute(Actor& actor) override
	{
        glm::vec3 newPos = actor.GetWorldPosition();
        newPos.x += _direction.x;
        newPos.y += _direction.y;
		actor.SetWorldPosition(newPos);
	}
private:
    Engine* _engine;
    glm::vec2 _direction;
};
