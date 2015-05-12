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
#include "Model/ModelNode.h"
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

#include "Game\Level\Level.h"

class Renderer
{
	NonLightingModelShaderProgram* noLightModelShader;
	LightingModelShaderProgram* lightModelShader;

	int camSwitch;
	std::queue<Camera*> cams;
	Camera* currentCam;
	FirstPersonCamera* freeCam;
	ThirdPersonCamera* carCam1;
	ThirdPersonCamera* carCam2;

	Model crate1;
	Model crate2;
	Model jeep;

	Skybox skybox;

	PhysicsWorld physicsWorld;

	GenericGameObject* crate1GameObject;
	RigidBody crate1PhysicsObject;
	GenericGameObject* crate2GameObject;
	RigidBody crate2PhysicsObject;
	
	CarGameObject* jeepGameObject;

	Level level1;
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

