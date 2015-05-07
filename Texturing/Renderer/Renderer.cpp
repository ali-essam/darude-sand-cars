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
	
	//spiderGameObject.physicsObject.addForce(glm::vec3(0,-98,0));
	//spiderPhysicsObject.SetPosition(glm::vec3(0, 300, -50));
	spiderPhysicsObject.SetMass(0.000001f);
	physicsWorld.physicsObjects.push_back(&(spiderPhysicsObject));
	
	spiderGameObject = new GenericGameObject(&spider, &spiderPhysicsObject);
	

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
	glm::mat4 VP = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix();


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
	//spiderModel = glm::translate(-0.0002f * (float)deltaTime, 0.f, 0.f) * spiderModel;
	spiderGameObject->Update(deltaTime);
	jeepGameObject->Update(deltaTime);
	//spiderGameObject.physicsObject.Update(deltaTime);
	physicsWorld.Update(deltaTime);
	HandleKeyboardInput(inputManager);
	HandleMouse(inputManager->GetMouseX(), inputManager->GetMouseY());
	myCamera->UpdateViewMatrix();
}

void Renderer::HandleKeyboardInput(InputManager* inputManager)
{
	if(inputManager->IsKeyPressed(GLFW_KEY_UP))
	{
		myCamera->Walk(.5);
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_DOWN))
	{
		myCamera->Walk(-0.5);
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_RIGHT))
	{
		myCamera->Strafe(0.5);
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_LEFT))
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
	if(inputManager->IsKeyPressed(GLFW_KEY_W)){
		jeepGameObject->Throttle();
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_S)){
		jeepGameObject->Break();
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_D)){
		jeepGameObject->SteerRight();
	}
	if(inputManager->IsKeyPressed(GLFW_KEY_A)){
		jeepGameObject->SteerLeft();
	}
}

void Renderer::HandleMouse(double deltaX,double deltaY)
{
	/*if(deltaX !=0 || deltaY !=0)
		printf("Renderer::MOUSE = %f , %f \n",deltaX,deltaY);*/
	myCamera->Yaw(deltaX);
	myCamera->Pitch(deltaY);
}
