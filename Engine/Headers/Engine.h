#pragma once
#include "Gameplay\Transform.h"
#include "Gameplay\Actor.h"
#include "Gameplay\InputManager.h"
#include "Gameplay\Level.h"
#include "Gameplay\Camera\Camera.h"
#include "Primitives\Text.h"
#include "Resources\ActorHandle.h"
#include "Resources\StackAllocator.h"
#include "DebugVisuals.h"
#include "API.h"

constexpr size_t MAX_ACTORS = 512;

struct GLFWwindow;
class InputManager;
class ShaderLoader;
class Command;
class ENGINE_API Actor;
enum class Button;

struct EngineConfiguration {
	int width = 1024;
	int height = 768;
	const char* title = "Viper Engine";
	bool isHeadless = false;
	bool limitFPS = true;
};

class ENGINE_API Input {
private:
	InputManager* _input = nullptr;
public:
	Input(InputManager* manager) { _input = manager; }
};

class DefaultLevel : public Level 
{
	void OnBegin() override {}
	void Update(float deltaTime) override {}
	void OnShutdown() override {}
};

#define NEW_CLASS(engine, type, ...) new (engine->AllocMem(sizeof(type))) type(__VA_ARGS__)
class Engine {
private:
	GLFWwindow* _window = nullptr;
	InputManager* _input = nullptr;
	ShaderLoader* _shaderLoader = nullptr;
	EngineConfiguration _config;

	// This acts as a map that points to an actor given its ActorHandle ID.
	// It allows for actors to be relocated in memory while not breaking references.
	Actor* _actors[512] = { nullptr };
	Actor* _playerActor = nullptr;
	unsigned int _lastActorID = 0;
	StackAllocator _stack = StackAllocator(MAX_ACTORS * sizeof(Actor));
	
	float _deltaTime = 1.f/60.f; // Assume 60FPS on startup.
	Level* _activeLevel = new DefaultLevel();
	Camera* _activeCamera = nullptr;
	DebugVisuals _debugVisuals;
	StackAllocator::Marker _emptyMarker;
public:
	ENGINE_API int Init(const EngineConfiguration& config);
	ENGINE_API int Run();
	ENGINE_API int Shutdown();

	// ACTOR API (TEST)
	ENGINE_API const ActorHandle& SpawnActor();
	ENGINE_API const ActorHandle& SpawnActor(Actor* actor);
	ENGINE_API void DestroyActor(const ActorHandle& actor);
	ENGINE_API void TranslateActor(const ActorHandle& handle, float x, float y, float z);
	ENGINE_API void SetPlayerActor(const ActorHandle& handle);
	ENGINE_API Actor* GetActor(const ActorHandle& handle);
	ENGINE_API void SetInputMode(const InputMode& mode);
	ENGINE_API void AddInputCommand(Button button, Command* command);

	// LEVEL API (TEST)
	ENGINE_API void SetActiveLevel(Level* level);
	ENGINE_API void SetActiveCamera(Camera* cam);
	ENGINE_API const Camera* GetActiveCamera() { return _activeCamera; }

	// DEBUG API (TEST)
	ENGINE_API const DebugVisuals& GetDebugVisuals() { return _debugVisuals; }

	ENGINE_API float GetDeltaTime();

	ENGINE_API Input GetInput() { return Input(_input); }
	ENGINE_API const EngineConfiguration& GetConfig() { return _config; }
	ENGINE_API void* AllocMem(size_t size) { return _stack.Alloc(size); }
	ENGINE_API void FreeToMarker(StackAllocator::Marker marker) { _stack.FreeToMarker(marker); }
private:
	ActorHandle AssignFreeActorID();
	unsigned int CreateTypeHash(const ActorHandle& handle);
};