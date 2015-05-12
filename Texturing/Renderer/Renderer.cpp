#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>

Renderer::Renderer()
{
	camSwitch = 0;
}

Renderer::~Renderer()
{
	Cleanup();
}

void Renderer::Initialize()
{
	freeCam = new FirstPersonCamera();
	carCam1 = new ThirdPersonCamera(glm::vec3(0.f), 20.f, 8.f);
	carCam2 = new ThirdPersonCamera(glm::vec3(0.f), 7.f, .1f);
	cams.push(carCam1);
	cams.push(carCam2);
	cams.push(freeCam);
	currentCam = cams.front();
	// Projection matrix : 
	freeCam->SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,100000.0f);
	carCam1->SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,100000.0f);
	carCam2->SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,100000.0f);

	glm::vec3 objectPosition = glm::vec3(100, 0, 100);
	// View matrix : 
	freeCam->Reset(glm::vec3(0.0, 100.0, 0.0),
		objectPosition,
		glm::vec3(0, 1, 0));
	//////////////////////////////////////////////////////////////////////////
	noLightModelShader = new NonLightingModelShaderProgram();
	noLightModelShader->Initialize();

	lightModelShader = new LightingModelShaderProgram();
	lightModelShader->Initialize();

	DirectionalLightSource lightSource(glm::vec3(0.41f,5.f,0.41f), glm::normalize(glm::vec3(250,250,150)));
	lightModelShader->SetDirectionalLight(lightSource);

	/////////////////////////////////////////////////////////////////////////

	jeep.LoadFromFile("data\\models\\Jeep\\jeep1.3ds");
	jeep.Initialize();


	jeepGameObject = new CarGameObject(&jeep, "3DSMesh_2", "3DSMesh_0");
	jeepGameObject->SetPosition(glm::vec3(0, 0, 210));
	physicsWorld.physicsObjects.push_back(jeepGameObject->GetPhysicsObject());

	skybox.LoadFromPath("data\\textures\\skybox\\");
	skybox.Initialize();

	level1.LoadFromFile("data\\levels\\1\\");
	jeepGameObject->SetPosition(level1.GetStartPosition());

	std::vector<PhysicsObject*> colliders = level1.GetPhysicsObjects();
	for (int i = 0; i < colliders.size(); i++)
	{
		physicsWorld.physicsObjects.push_back(colliders[i]);
	}

	crate1.LoadFromFile("data\\models\\Crate\\Crate1.3ds");
	crate1.Initialize();
	crate1PhysicsObject.SetMass(0.000001f);
	crate1PhysicsObject.SetPosition(level1.GetStartPosition() + glm::vec3(10.f, 3.f, 200.f));
	crate1PhysicsObject.AddForce(glm::vec3(-0.00001f,0.f,-0.0001f)); 
	physicsWorld.physicsObjects.push_back(&(crate1PhysicsObject));

	crate1GameObject = new GenericGameObject(&crate1, &crate1PhysicsObject);
	crate1GameObject->Scale(glm::vec3(6.f));

	crate2.LoadFromFile("data\\models\\Crate\\Crate1.3ds");
	crate2.Initialize();
	crate2PhysicsObject.SetMass(0.000001f);
	crate2PhysicsObject.SetPosition(level1.GetStartPosition() + glm::vec3(-10.f, 3.f, 200.f));
	crate2PhysicsObject.AddForce(glm::vec3(0.0001f,0.f,-0.0001f)); 
	physicsWorld.physicsObjects.push_back(&(crate2PhysicsObject));

	crate2GameObject = new GenericGameObject(&crate2, &crate2PhysicsObject);
	crate2GameObject->Scale(glm::vec3(6.f));
}

void Renderer::Draw()
{
	glm::mat4 VP = currentCam->GetProjectionMatrix() * currentCam->GetViewMatrix();


	lightModelShader->UseProgram();
	lightModelShader->BindVPMatrix(&VP[0][0]);

	crate1GameObject->Render(lightModelShader);
	crate2GameObject->Render(lightModelShader);
	jeepGameObject->Render(lightModelShader);
	level1.Render(lightModelShader);


	// No Lighting models
	noLightModelShader->UseProgram();
	noLightModelShader->BindVPMatrix(&VP[0][0]);
	skybox.Render(noLightModelShader);
}

void Renderer::Cleanup()
{
	noLightModelShader->CleanUp();
	lightModelShader->CleanUp();
	// CleanUp Models
}

void Renderer::Update(double deltaTime, InputManager* inputManager)
{
	int c = 0;
	crate1GameObject->Update(deltaTime);
	crate2GameObject->Update(deltaTime);
	jeepGameObject->Update(deltaTime);
	physicsWorld.Update(deltaTime);
	HandleKeyboardInput(inputManager);
	HandleMouse(inputManager->GetMouseX(), inputManager->GetMouseY());

	carCam1->setObjectPosition(jeepGameObject->GetPosition() + glm::vec3(0.f, 10.f, 0.f));
	carCam1->setYawAngle(-(jeepGameObject->GetHeadingAngle() + 3.14f/2.f));

	carCam2->setObjectPosition(jeepGameObject->GetPosition() + glm::vec3(0.f, 7.f, 0.f));
	carCam2->setYawAngle(-(jeepGameObject->GetHeadingAngle() + 3.14f/2.f));

	currentCam->UpdateViewMatrix();
}

void Renderer::HandleKeyboardInput(InputManager* inputManager)
{
	if(inputManager->IsKeyPressed(GLFW_KEY_UP))
	{
		freeCam->Walk(1.0);
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_DOWN))
	{
		freeCam->Walk(-1.0);
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_RIGHT))
	{
		freeCam->Strafe(1.0);
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_LEFT))
	{
		freeCam->Strafe(-1.0);
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_SPACE) || inputManager->IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		freeCam->Walk(10.0);
	}
	if(inputManager->IsKeyPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		freeCam->Fly(-1.0);
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_W)){
		jeepGameObject->Throttle();
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_S)){
		jeepGameObject->Break();
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_D)){
		jeepGameObject->SteerRight();
		//printf("CarHeading: %.3f\n", jeepGameObject->GetHeadingAngle());
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_A)){
		jeepGameObject->SteerLeft();
		//printf("CarHeading: %.3f\n", jeepGameObject->GetHeadingAngle());
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_C)){
		if(camSwitch!=0)
		{
			camSwitch++;
			if(camSwitch > 10)
				camSwitch = 0;
		}
		else
		{
			Camera* prevCam = cams.front();
			cams.pop();
			cams.push(prevCam);
			currentCam = cams.front();
			camSwitch++;
		}
	}
}

void Renderer::HandleMouse(double deltaX,double deltaY)
{
	if (deltaX == 0 && deltaY == 0) return;
	freeCam->Yaw(deltaX);
	freeCam->Pitch(deltaY);
}
