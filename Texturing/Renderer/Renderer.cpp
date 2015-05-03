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
	//myCamera = std::unique_ptr<FPCamera>(new FPCamera());
	myCamera = std::unique_ptr<EulerCamera>(new EulerCamera());

	// Projection matrix : 
	myCamera->SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,100000.0f);

	// View matrix : 
	myCamera->Reset(0.0,0.0,5.0,
		0,0,0,
		0,1,0);
	//////////////////////////////////////////////////////////////////////////
	graphicsDevice = new GraphicsDevice();
	graphicsDevice->Initialize();


	//house.LoadFromFile("data\\models\\Wheel\\cart_wheel.3ds");
	spider.LoadFromFile("data\\models\\Spider\\spider.obj");
	spider.Initialize();
	spiderModel = glm::translate(2.0f, 0.0f, 1.0f) * glm::scale(0.01f, 0.01f, 0.01f);
	
	spiderGameObject.model = &spider;
	spiderGameObject.Initialize();
	spiderGameObject.physicsObject.SetMass(1);
	spiderGameObject.physicsObject.SetPosition(glm::vec3(0, 300, -50));
	//spiderGameObject.physicsObject.addForce(glm::vec3(0,-98,0));
	physicsWorld.physicsObjects.push_back(&(spiderGameObject.physicsObject));

	wheel.LoadFromFile("data\\models\\Wheel\\cart_wheel.3ds");
	wheel.Initialize();

	house.LoadFromFile("data\\models\\House\\house.obj");
	house.Initialize();

	jeep.LoadFromFile("data\\models\\Jeep\\jeep1.3ds");
	jeep.Initialize();

	jeepGameObject.model = &jeep;
	jeepGameObject.Initialize();
	jeepGameObject.physicsObject.SetMass(1);
	jeepGameObject.physicsObject.SetPosition(glm::vec3(0, -30, -55));
	jeepGameObject.physicsObject.AddForce(glm::vec3(0,100,0));
	physicsWorld.physicsObjects.push_back(&(jeepGameObject.physicsObject));

	skybox.LoadFromPath("data\\textures\\skybox\\");
	skybox.Initialize();
}

void Renderer::Draw()
{
	graphicsDevice->BeginDraw();

	glm::mat4 VP = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix();
	graphicsDevice->BindVPMatrix(&VP[0][0]);

	glm::mat4 houseM = glm::scale(0.05f, 0.05f, 0.05f);
	graphicsDevice->BindModelMatrix(&houseM[0][0]);

	house.Render(graphicsDevice, glm::translate(2.0f, 0.0f, 0.0f) * glm::scale(0.2f, 0.2f, 0.2f));
	//jeep.Render(graphicsDevice, glm::translate(-1.0f, 0.0f, 0.0f) * glm::scale(0.1f, 0.1f, 0.1f) * glm::rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
	//spider.Render(graphicsDevice, spiderModel);
	wheel.Render(graphicsDevice, glm::translate(-4.0f, 0.0f, 0.0f) * glm::scale(0.1f, 0.1f, 0.1f)* glm::rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f)));

	skybox.Render(graphicsDevice);

	spiderGameObject.Render(graphicsDevice);
	jeepGameObject.Render(graphicsDevice);
}

void Renderer::Cleanup()
{
	graphicsDevice->CleanUp();
	// CleanUp Models
}

void Renderer::Update(double deltaTime, InputManager* inputManager)
{
	int c = 0;
	//spiderModel = glm::translate(-0.0002f * (float)deltaTime, 0.f, 0.f) * spiderModel;
	spiderGameObject.Update(deltaTime);
	jeepGameObject.Update(deltaTime);
	//spiderGameObject.physicsObject.Update(deltaTime);
	physicsWorld.Update(deltaTime);
	HandleKeyboardInput(inputManager);
	HandleMouse(inputManager->GetMouseX(), inputManager->GetMouseY());
	myCamera->UpdateViewMatrix();
}

void Renderer::HandleKeyboardInput(InputManager* inputManager)
{
	if(inputManager->IsKeyPressed(GLFW_KEY_UP) || inputManager->IsKeyPressed(GLFW_KEY_W))
	{
		myCamera->Walk(50);
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_DOWN) || inputManager->IsKeyPressed(GLFW_KEY_S))
	{
		myCamera->Walk(-0.5);
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_RIGHT) || inputManager->IsKeyPressed(GLFW_KEY_D))
	{
		myCamera->Strafe(0.5);
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_LEFT) || inputManager->IsKeyPressed(GLFW_KEY_A))
	{
		myCamera->Strafe(-0.5);
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_SPACE) || inputManager->IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		myCamera->Fly(5);
	}
	if(inputManager->IsKeyPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		myCamera->Fly(-0.5);
	}
}

void Renderer::HandleMouse(double deltaX,double deltaY)
{
	/*if(deltaX !=0 || deltaY !=0)
		printf("Renderer::MOUSE = %f , %f \n",deltaX,deltaY);*/
	myCamera->Yaw(deltaX);
	myCamera->Pitch(deltaY);
}
