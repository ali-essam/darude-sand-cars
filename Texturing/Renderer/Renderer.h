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
#include "FPCamera/FPCamera.h"
#include "EulerCamera/EulerCamera.h"
#include "GraphicsDevice\GraphicsDevice.h"
#include "InputManager\InputManager.h"

#include "Skybox\Skybox.h"
#include "Game\GameObject.h"
#include "PhysicsEngine\PhysicsWorld.h"

class Renderer
{
	GraphicsDevice* graphicsDevice;

	//std::unique_ptr<FPCamera> myCamera;
	std::unique_ptr<EulerCamera> myCamera;

	Model house;
	Model spider;
	Model wheel;
	Model jeep;

	Skybox skybox;

	PhysicsWorld physicsWorld;

	GameObject spiderGameObject;
	GameObject jeepGameObject;

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

