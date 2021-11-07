#include "Gameplay\Actor.h"

void Actor::Update(float deltaTime) 
{
	
}

void Actor::Draw(glm::mat4 viewProjection)
{
	_visuals->Draw(viewProjection);
}