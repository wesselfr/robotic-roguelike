#pragma once
#include "Gameplay\Components\QuadVisual.h"
#include "Gameplay\Components\Physics\RigidBodyComponent.h"
#include "Physics\AABB.h"
#include "Resources\ActorHandle.h"
#include "API.h"

class NullVisual : public VisualComponent {};

// Common baseclass for interactable objects in the game.
class Actor : public Transform
{
protected:
	VisualComponent* _visuals = new NullVisual();
	RigidBodyComponent* _rigidBody = nullptr;
	ActorHandle _handle;
public:
	Actor() {}
	Actor(VisualComponent* visual) 
	{ 
		_visuals = visual;
		_visuals->SetTransform(this);
		_visuals->Init();
	}
	~Actor() 
	{ 
		_visuals->Shutdown(); 
		delete _visuals; 
	}

	ENGINE_API virtual void Update(float deltaTime);
	ENGINE_API virtual void Draw(glm::mat4 viewProjection);

	ENGINE_API inline VisualComponent* GetVisualComponent() { return _visuals; }
	ENGINE_API inline RigidBodyComponent* GetRigidBody() { return _rigidBody; }

	void SetActorHandle(const ActorHandle& handle) { _handle = handle; }
	ENGINE_API const ActorHandle& GetActorHandle() { return _handle; }
};