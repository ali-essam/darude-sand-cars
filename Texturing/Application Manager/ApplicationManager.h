#ifndef ApplicationManager_h__
#define ApplicationManager_h__
#include <Windows.h>
#include <gl/glew.h>
#include <gl/glfw3.h>
#include <memory>
#include "Renderer/Renderer.h"
#include "InputManager/InputManager.h"

class ApplicationManager
{

	int mOpenGLMajorVersion;
	int mOpenGLMinorVersion;
	double mTime;

	GLFWwindow* mWindow; 
	std::unique_ptr<Renderer> mRenderer;

	void InitializeComponents();
	static void WindowResized(GLFWwindow* window, int width, int height);

	InputManager* inputManager;

	static int WindowSizeWidth;
	static int WindowSizeHeight;

public:



	ApplicationManager(int pOpenGLMajorVersion, int pOpenGLMinorVersion);

	bool InitalizeApplication(int pWindowSizeWidth, int pWindowSizeHeight);
	void StartMainLoop();
	void CloseApplication();

	~ApplicationManager(void);
};
#endif // ApplicationManager_h__

