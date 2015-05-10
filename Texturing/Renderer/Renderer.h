#ifndef Renderer_h__
#define Renderer_h__

#include <gl/glew.h>
#include <gl/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <queue>


#include "Shaders/shader.hpp"
#include "Texture/texture.h"
#include "Model/Model.h"
#include "ShaderProgram\NonLightingModelShaderProgram.h"
#include "ShaderProgram\LightingModelShaderProgram.h"
#include "Lighting\DirectionalLightSource.h"
#include "Camera\FirstPersonCamera\FirstPersonCamera.h"
#include "Camera\ThirdPersonCamera\ThirdPersonCamera.h"
#include "InputManager\InputManager.h"

#include "Skybox\Skybox.h"
#include "Game\GenericGameObject.h"
#include "Game\CarGameObject.h"
#include "PhysicsEngine\PhysicsWorld.h"
#include "PhysicsEngine\RigidBody.h"
#include "PhysicsEngine\CarPhysicsObject.h"
#include "PhysicsEngine\PhysicsObject.h"

class Renderer
{
	NonLightingModelShaderProgram* noLightModelShader;
	LightingModelShaderProgram* lightModelShader;

	std::queue<Camera*> cams;
	Camera* currentCam;
	FirstPersonCamera* freeCam;
	ThirdPersonCamera* carCam1;
	ThirdPersonCamera* carCam2;
	glm::vec3 objectPosition;
	Model house;
	Model spider;
	Model wheel;
	Model jeep;
	Model track;

	Skybox skybox;

	PhysicsWorld physicsWorld;

	GenericGameObject* spiderGameObject;
	CarGameObject* jeepGameObject;
	RigidBody spiderPhysicsObject;

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

