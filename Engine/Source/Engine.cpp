#include "Engine.h"
#include <iostream>
#include "xxhash64.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
using namespace glm;

#include "Log.h"
#include "Resources\ShaderLoader.h"
#include "Primitives\Quad.h"
#include "Primitives\Line.h"
#include "Gameplay\InputManager.h"
#include "Gameplay\Components\TileVisual.h"
#include "Gameplay\Camera\FollowCamera.h"
#include "Gameplay\BulletPool.h"

int Engine::Init(const EngineConfiguration& config) 
{ 
	_config = config;

	if (!config.isHeadless) 
	{
		if (!glfwInit())
		{
			Log::LogError("Failed to initialize GLFW");
		}

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		_window = glfwCreateWindow(config.width, config.height, config.title, NULL, NULL);
		if (_window == nullptr)
		{
			Log::LogError("Failed to initialize window..");
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(_window);
		glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);
		glClearColor(0, 0.168f, 0.211f, 1);

		if (glewInit() != GLEW_OK)
		{
			Log::LogError("Could not initialize GLEW");
			return -1;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// These lines to remove the 60FPS cap
		if (!config.limitFPS) {
			glfwMakeContextCurrent(_window);
			glfwSwapInterval(0);
		}

		_shaderLoader = new ShaderLoader();
		_debugVisuals.Init(static_cast<float>(config.width), static_cast<float>(config.height));
	}
	else {
		Log::LogWarning("Engine is running in headless mode.");
	}

	_activeCamera = new Camera(glm::vec3(0, 0, 0), _config.width, _config.height);
	
	_input = new InputManager();
	_input->Initialize(_window);

	_emptyMarker = _stack.GetMarker();
	
	return 0;
}

int Engine::Run()
{
	double lastTime = glfwGetTime();
	while (glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(_window) == 0) {
		double currentTime = glfwGetTime(); 
		_deltaTime = static_cast<float>(currentTime - lastTime);
		lastTime = currentTime;
		_activeCamera->Update(_deltaTime);
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		_input->HandleInput();

		_activeLevel->Update(_deltaTime);

		// Todo: Update Actors in parallel.
		for (const auto& _actor : _actors)
		{
			if (_actor != nullptr) 
			{
				// Currently the Actors need to be drawn first before they are updated.
				// This is because Actors can be destroyed during the update function.
				// When refactoring and updating the Actor in parallel, the Actor should first be updated before it gets drawn.
				_actor->Draw(_activeCamera->GetViewProjection());
				_actor->Update(_deltaTime);
			}
		}

		if (!_config.isHeadless) {
			DebugVisuals::GetInstance()->DrawText(glm::vec3(20, _config.height - 50, 0), glm::vec3(1.f), "MEM USAGE: %i / %i", (int)(_stack.GetMarker() - _emptyMarker), MAX_ACTORS * sizeof(Actor));
			DebugVisuals::GetInstance()->DrawText(glm::vec3(20, _config.height - 60, 0), glm::vec3(1.f), "FPS: %i", (int)(1.f / _deltaTime));
		}

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
	return 0;
}

int Engine::Shutdown() 
{
	_activeLevel->OnShutdown();
	delete _activeLevel;

	if (!_config.isHeadless) {
		glfwTerminate();
	}
	
	// Delete all actors in stack.
	_stack.Clear();

	glfwTerminate();
	return 0;
}

const ActorHandle& Engine::SpawnActor() {
	ActorHandle handle = AssignFreeActorID();
	assert(handle.ID < MAX_ACTORS);
	_actors[handle.ID] = new Actor(new TileVisual());
	handle.TypeHash = CreateTypeHash(handle);
	_actors[handle.ID]->SetActorHandle(handle);
	return _actors[handle.ID]->GetActorHandle();
}

const ActorHandle& Engine::SpawnActor(Actor* actor) 
{
	ActorHandle handle = AssignFreeActorID();
	assert(handle.ID < MAX_ACTORS);

	_actors[handle.ID] = actor;

	// Assign a Handle to the actor.
	handle.TypeHash = CreateTypeHash(handle);
	_actors[handle.ID]->SetActorHandle(handle);

	// Return the handle.
	return actor->GetActorHandle();
}

void Engine::DestroyActor(const ActorHandle& actor) 
{
	int id = actor.ID;
	// Delete if the actor matches the given TypeHash. 
	// This ensures we are not deleting a stale object.	
	if (_actors[id]->GetActorHandle().TypeHash == actor.TypeHash) {
		_actors[id] = nullptr;
	}
}

void Engine::TranslateActor(const ActorHandle& handle, float x, float y, float z) 
{
	assert(handle.ID <= _lastActorID);
	_actors[handle.ID]->Translate(glm::vec3(x, y, z));
}

void Engine::SetPlayerActor(const ActorHandle& handle) 
{
	assert(handle.ID <= _lastActorID);
	_playerActor = _actors[handle.ID];
	_input->SetActiveActor(_playerActor);
}

Actor* Engine::GetActor(const ActorHandle& handle) 
{
	assert(handle.ID <= _lastActorID);
	Actor* actor = _actors[handle.ID];
	// Ensure that the requested Actor has the same TypeHash as the stored Actor.
	// This should prevent stale objects from being returned.
	if (actor->GetActorHandle().TypeHash == handle.TypeHash) {
		return actor;
	}
	else {
		return nullptr;
	}
}

void Engine::AddInputCommand(Button button, Command* command) 
{
	_input->SetButtonCommand(button, command);
}

void Engine::SetActiveLevel(Level* level)
{
	assert(level != nullptr);

	// Shutdown previous level
	_activeLevel->OnShutdown();
	delete _activeLevel;

	// Initialize new level
	level->engine = this;
	level->OnBegin();

	// Set level active.
	_activeLevel = level;
}

void Engine::SetActiveCamera(Camera* camera) 
{
	assert(camera != nullptr);
	delete _activeCamera;
	_activeCamera = camera;
}

float Engine::GetDeltaTime() 
{
	return _deltaTime;
}

ActorHandle Engine::AssignFreeActorID() 
{
	//Todo: Check free slots.
	return { _lastActorID++, 0 };
}

// Use actor handle to generate a hash based on the ActorType
// xxHash based on: https://create.stephan-brumme.com/xxhash/
unsigned int Engine::CreateTypeHash(const ActorHandle& handle) 
{
	return static_cast<unsigned int>(XXHash64::hash(_actors[handle.ID], sizeof(Actor), 0));
}
