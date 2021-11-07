#pragma once
#include <iostream>
#include "Actor.h"
#include "Command.h"
#include "API.h"

static Command emptyCommand;

enum class ENGINE_API Button {
	//Gamepad
	GamepadArrowUp,
	GamepadArrowRight,
	GamepadArrowDown,
	GamepadArrowLeft,
	GamepadTriangleButton,
	GamepadCircleButton,
	GamepadCrossButton,
	GamepadSquareButton,

	//Keyboard
	KeyW,
	KeyA,
	KeyS,
	KeyD,
	KeyQ,
	KeyE,
	KeySpace,

	//Mouse
	MouseLeft,
	MouseMiddle,
	MouseRight,
};

class InputManager 
{
public:
	void Initialize(GLFWwindow* window);
	void HandleInput();
	const glm::vec2& GetLeftAxis();
	const glm::vec2& GetRightAxis();

	void SetButtonCommand(Button button, Command* command);
	void SetActiveActor(Actor* actor);
private:
	static void JoystickEventCallback(int jid, int event);

	// Gamepad Callbacks
	Command* _gamepadArrowUp = &emptyCommand;
	Command* _gamepadArrowRight = &emptyCommand;
	Command* _gamepadArrowDown = &emptyCommand;
	Command* _gamepadArrowLeft = &emptyCommand;
	Command* _gamepadTriangleButton = &emptyCommand;
	Command* _gamepadCircleButton = &emptyCommand;
	Command* _gamepadCrossButton = &emptyCommand;
	Command* _gamepadSquareButton = &emptyCommand;
	// Keyboard Callbacks
	Command* _keyW = &emptyCommand;
	Command* _keyA = &emptyCommand;
	Command* _keyS = &emptyCommand;
	Command* _keyD = &emptyCommand;
	Command* _keyQ = &emptyCommand;
	Command* _keyE = &emptyCommand;
	Command* _keySpace = &emptyCommand;
	// Mouse Callback
	Command* _mouseLeft = &emptyCommand;
	Command* _mouseMiddle = &emptyCommand;
	Command* _mouseRight = &emptyCommand;

	// Input Manager data
	GLFWwindow* _window = nullptr;
	Actor* _activeActor = nullptr;
	glm::vec2 _gamepadLeftAxis = glm::vec2(0,0);
	glm::vec2 _gamepadRightAxis = glm::vec2(0,0);
};