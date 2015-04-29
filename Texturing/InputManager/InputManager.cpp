#include "InputManager.h"

InputManager::InputManager(GLFWwindow* window):mWindow(window), MOUSE_SPEED(0.005)
{
}

InputManager::~InputManager()
{
}

void InputManager::AddPressedKey(int key)
{
	pressedKeys.insert(key);
}

bool InputManager::IsKeyPressed(int key)
{
	return pressedKeys.count(key) > 0;
}

void InputManager::Initialize()
{
	// Enusre we can capture keys even after they're released.
	glfwSetInputMode(mWindow, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(mWindow, GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE);
	// Hide Mouse From Screen.
	glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	this->Clear();
}

void InputManager::Clear()
{
	pressedKeys.clear();
	this->CenterMouse();
	mouseX = 0;
	mouseY = 0;
}

void InputManager::SetMouse(double x, double y)
{
	mouseX = x;
	mouseY = y;
}

double InputManager::GetMouseX()
{
	return mouseX;
}

double InputManager::GetMouseY()
{
	return mouseY;
}

void InputManager::Update()
{
	this->UpdateMouse();
	this->UpdateKeyboard();
}

void InputManager::UpdateMouse()
{
	double mouseXPos, mouseYPos;
	int windowSizeWidth, windowSizeHeight;
	glfwGetCursorPos(mWindow, &mouseXPos, &mouseYPos);
	glfwGetWindowSize(mWindow, &windowSizeWidth, &windowSizeHeight);

	double movedDistanceX = double(windowSizeWidth/2 - mouseXPos)*MOUSE_SPEED;
	double movedDistanceY = double(windowSizeHeight/2 - mouseYPos)*MOUSE_SPEED;

	this->SetMouse(movedDistanceX, movedDistanceY);

	//Force the new position of the mouse to be in the middle of the window
	this->CenterMouse();

	for (int i = 0; i < 8; i++)
	{
		if(glfwGetMouseButton(mWindow, i ) == GLFW_PRESS)
			this->AddPressedKey(i);
	}
}

void InputManager::CenterMouse()
{
	int windowSizeWidth, windowSizeHeight;
	glfwGetWindowSize(mWindow, &windowSizeWidth, &windowSizeHeight);
	glfwSetCursorPos(mWindow, windowSizeWidth/2, windowSizeHeight/2); 
}

void InputManager::UpdateKeyboard()
{
	for (int i = 32; i <= 348; i++)
	{
		if(glfwGetKey(mWindow, i ) == GLFW_PRESS)
			this->AddPressedKey(i);
	}
}