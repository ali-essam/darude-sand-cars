#ifndef Renderer_h__
#define Renderer_h__

#include <gl/glew.h>
#include <gl/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>


#include "Shaders/shader.hpp"
#include "Texture/texture.h"
#include "Model/Model.h"
#include "Camera\FirstPersonCamera\FirstPersonCamera.h"
#include "Camera\ThirdPersonCamera\ThirdPersonCamera.h"
#include "GraphicsDevice\GraphicsDevice.h"
#include "InputManager\InputManager.h"

#include "Skybox\Skybox.h"

class Renderer
{
	GraphicsDevice* graphicsDevice;

	std::unique_ptr<Camera> myCamera;
	glm::vec3 objectPosition;
	Model house;
	Model spider;
	Model wheel;
	Model jeep;

	Skybox skybox;

	glm::mat4 spiderModel;
public:
    Renderer();
    ~Renderer();
    
    void Initialize();
    void Draw();
	void HandleKeyboardInput(InputManager* inputManager);
	void HandleMouse(double deltaX,double deltaY);
	void Update(double deltaTime, InputManager* inputManager);
    void Cleanup();
};

#endif // Renderer_h__

