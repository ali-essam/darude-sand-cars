#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>

Renderer::Renderer()
{

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

	objectPosition = glm::vec3(0, 0, 0);
	// View matrix : 
	freeCam->Reset(glm::vec3(0.0, 100.0, 0.0),
		objectPosition,
		glm::vec3(0, 1, 0));
	//////////////////////////////////////////////////////////////////////////
	noLightModelShader = new NonLightingModelShaderProgram();
	noLightModelShader->Initialize();

	lightModelShader = new LightingModelShaderProgram();
	lightModelShader->Initialize();

	DirectionalLightSource lightSource(glm::vec3(0.1f,5.f,0.1f), glm::normalize(glm::vec3(250,250,150)));
	lightModelShader->SetDirectionalLight(lightSource);

	/////////////////////////////////////////////////////////////////////////
	track.LoadFromFile("data\\models\\Track01\\track01_.3ds");
	track.Initialize();

	spider.LoadFromFile("data\\models\\Spider\\spider.obj");
	spider.Initialize();
	spiderPhysicsObject.SetMass(0.000001f);
	physicsWorld.physicsObjects.push_back(&(spiderPhysicsObject));
	
	spiderGameObject = new GenericGameObject(&spider, &spiderPhysicsObject);
	spiderModel = glm::scale(0.01f, 0.01f, 0.01f);

	wheel.LoadFromFile("data\\models\\Wheel\\cart_wheel.3ds");
	wheel.Initialize();

	house.LoadFromFile("data\\models\\House\\house.obj");
	house.Initialize();

	jeep.LoadFromFile("data\\models\\Jeep\\jeep1.3ds");
	jeep.Initialize();

	
	jeepGameObject = new CarGameObject(&jeep);
	jeepGameObject->SetPosition(glm::vec3(0, 0, 210));
	physicsWorld.physicsObjects.push_back(jeepGameObject->GetPhysicsObject());

	skybox.LoadFromPath("data\\textures\\skybox\\");
	skybox.Initialize();
}

void Renderer::Draw()
{
	glm::mat4 VP = currentCam->GetProjectionMatrix() * currentCam->GetViewMatrix();


	lightModelShader->UseProgram();
	lightModelShader->BindVPMatrix(&VP[0][0]);

	track.Render(lightModelShader, glm::translate(0.f, -30.f, 0.f));
	
	glm::mat4 houseM = glm::scale(0.05f, 0.05f, 0.05f);

	house.Render(lightModelShader, glm::translate(2.0f, 0.0f, 0.0f) * glm::scale(0.2f, 0.2f, 0.2f));
	wheel.Render(lightModelShader, glm::translate(-4.0f, 0.0f, 0.0f) * glm::scale(0.1f, 0.1f, 0.1f)* glm::rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f)));

	spiderGameObject->Render(lightModelShader);
	jeepGameObject->Render(lightModelShader);

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
	spiderGameObject->Update(deltaTime);
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
		freeCam->Fly(1.0);
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
		printf("CarHeading: %.3f\n", jeepGameObject->GetHeadingAngle());
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_A)){
		jeepGameObject->SteerLeft();
		printf("CarHeading: %.3f\n", jeepGameObject->GetHeadingAngle());
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_C)){
		Camera* prevCam = cams.front();
		cams.pop();
		cams.push(prevCam);
		currentCam = cams.front();
	}
}

void Renderer::HandleMouse(double deltaX,double deltaY)
{
	if (deltaX == 0 && deltaY == 0) return;
	freeCam->Yaw(deltaX);
	freeCam->Pitch(deltaY);
}
