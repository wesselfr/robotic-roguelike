#include "Gameplay\InputManager.h"
#include "Log.h"

void InputManager::Initialize(GLFWwindow* window) 
{
	_window = window;
	glfwSetJoystickCallback(&InputManager::JoystickEventCallback);
}

// Todo: split into two input managers (Joystick & Keyboard-Mouse)
void InputManager::HandleInput() 
{
	// When no actor is active, return early.
	if (_activeActor == nullptr) { Log::LogWarning("No active actor found", "Input"); return; }

	int joystickPresent = glfwJoystickPresent(GLFW_JOYSTICK_LAST);
	if (joystickPresent)
	{
		//Handle joystick input
		int joystickButtonCount = 0;
		const unsigned char* joystickButtonStates = glfwGetJoystickButtons(GLFW_JOYSTICK_LAST, &joystickButtonCount);

		int joystickAxisCount = 0;
		const float* joystickAxisStates = glfwGetJoystickAxes(GLFW_JOYSTICK_LAST, &joystickAxisCount);

		// PS4 controller requires 6 input axis to work correctly.
		if (joystickAxisCount >= 6) {
			_gamepadLeftAxis = glm::vec2(joystickAxisStates[0], joystickAxisStates[1]);
			_gamepadRightAxis = glm::vec2(joystickAxisStates[2], joystickAxisStates[5]);
		}

		// To support all the PS4 controller buttons we need atleast 17 buttons.
		if (joystickButtonCount >= 17) 
		{
			if (joystickButtonStates[0]) { _gamepadSquareButton->Execute(*_activeActor); }
			if (joystickButtonStates[1]) { _gamepadCrossButton->Execute(*_activeActor); }
			if (joystickButtonStates[2]) { _gamepadCircleButton->Execute(*_activeActor); }
			if (joystickButtonStates[3]) { _gamepadTriangleButton->Execute(*_activeActor); }

			if (joystickButtonStates[14]) { _gamepadArrowUp->Execute(*_activeActor); }
			if (joystickButtonStates[15]) { _gamepadArrowRight->Execute(*_activeActor); }
			if (joystickButtonStates[16]) { _gamepadArrowDown->Execute(*_activeActor); }
			if (joystickButtonStates[17]) { _gamepadArrowLeft->Execute(*_activeActor); }
		}
	}

	// Keyboard fallback.
	if (glfwGetKey(_window, GLFW_KEY_W)) { _keyW->Execute(*_activeActor); }
	if (glfwGetKey(_window, GLFW_KEY_A)) { _keyA->Execute(*_activeActor); }
	if (glfwGetKey(_window, GLFW_KEY_S)) { _keyS->Execute(*_activeActor); }
	if (glfwGetKey(_window, GLFW_KEY_D)) { _keyD->Execute(*_activeActor); }
	if (glfwGetKey(_window, GLFW_KEY_Q)) { _keyQ->Execute(*_activeActor); }
	if (glfwGetKey(_window, GLFW_KEY_E)) { _keyE->Execute(*_activeActor); }
	if (glfwGetKey(_window, GLFW_KEY_SPACE)) { _keySpace->Execute(*_activeActor); }

	// Mouse buttons
	if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT)) { _mouseLeft->Execute(*_activeActor); }
	if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_MIDDLE)) { _mouseMiddle->Execute(*_activeActor); }
	if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_RIGHT)) { _mouseRight->Execute(*_activeActor); }
}

const glm::vec2& InputManager::GetLeftAxis() 
{
	return _gamepadLeftAxis;
}

const glm::vec2& InputManager::GetRightAxis() 
{
	return _gamepadRightAxis;
}

void InputManager::SetButtonCommand(Button button, Command* command) 
{
	switch (button)
	{
	case Button::GamepadArrowUp:
		_gamepadArrowUp = command;
		break;
	case Button::GamepadArrowRight:
		_gamepadArrowRight = command;
		break;
	case Button::GamepadArrowDown:
		_gamepadArrowDown = command;
		break;
	case Button::GamepadArrowLeft:
		_gamepadArrowLeft = command;
		break;
	case Button::GamepadTriangleButton:
		_gamepadTriangleButton = command;
		break;
	case Button::GamepadCircleButton:
		_gamepadCircleButton = command;
		break;
	case Button::GamepadCrossButton:
		_gamepadCrossButton = command;
		break;
	case Button::GamepadSquareButton:
		_gamepadSquareButton = command;
		break;
	case Button::KeyW:
		_keyW = command;
		break;
	case Button::KeyA:
		_keyA = command;
		break;
	case Button::KeyS:
		_keyS = command;
		break;
	case Button::KeyD:
		_keyD = command;
		break;
	case Button::KeyQ:
		_keyQ = command;
		break;
	case Button::KeyE:
		_keyE = command;
		break;
	case Button::KeySpace:
		_keySpace = command;
		break;
	case Button::MouseLeft:
		_mouseLeft = command;
		break;
	case Button::MouseMiddle:
		_mouseMiddle = command;
		break;
	case Button::MouseRight:
		_mouseRight = command;
		break;
	default:
		break;
	}
}

void InputManager::SetActiveActor(Actor* actor) 
{
	_activeActor = actor;
}

void InputManager::JoystickEventCallback(int jid, int event) 
{
	if (event == GLFW_CONNECTED) 
	{
		Log::LogMessage("Joystick connected: %s", "Input", glfwGetJoystickName(jid));
	}
	else if (event == GLFW_DISCONNECTED) 
	{
		Log::LogMessage("Joystick disconnected: %s", "Input", glfwGetJoystickName(jid));
	}
}