#include "Engine.h"
#include "Actors/Player.h"
#include "Gameplay/Components/TileVisual.h"


Player::Player(Engine* engine) : Actor()
{
	_aabb = NEW_CLASS(engine, AABB, this, glm::vec2(32,32));
	_rigidBody = NEW_CLASS(engine, RigidBodyComponent, this, _aabb);

	Texture texture("Assets/Textures/Player.png");

	TileVisual* tileVisual = NEW_CLASS(engine, TileVisual);
	tileVisual->SetSprite(0,texture);
	_visuals = tileVisual;
	_visuals->SetTransform(this);
	_visuals->Init();

	texture.Free();
}

void Player::Update(float deltaTime)
{

}

