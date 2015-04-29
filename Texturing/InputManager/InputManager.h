#ifndef InputManager_h__
#define InputManager_h__

#include <set>
#include <gl/glfw3.h>

class InputManager
{
	std::set<int> pressedKeys;
	double mouseX;
	double mouseY;
	const double MOUSE_SPEED;
	GLFWwindow* mWindow;

	void UpdateMouse();
	void CenterMouse();
	void UpdateKeyboard();
	void AddPressedKey(int key);
	void SetMouse(double x, double y);
public:
	InputManager(GLFWwindow* window);
	~InputManager();

	void Initialize();
	void Update();
	void Clear();
	bool IsKeyPressed(int key);
	double GetMouseX();
	double GetMouseY();
};

#endif //InputManager_h__