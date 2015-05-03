#include "PhysicsWorld.h"

PhysicsWorld::PhysicsWorld()
{
}

PhysicsWorld::~PhysicsWorld()
{
}

void PhysicsWorld::Update(float dt)
{
	for (int i = 0; i < physicsObjects.size(); i++)
	{
		physicsObjects[i]->Update(dt);
	}
	for (int i = 0; i < physicsObjects.size(); i++)
	{
		for (int j = i+1; j < physicsObjects.size(); j++)
		{
			bool collided = physicsObjects[i]->GetBoundingBox()->IsIntersecting(*(physicsObjects[j]->GetBoundingBox()));
			if(collided)
			{
				glm::vec3 v1 = physicsObjects[i]->GetVelocity();
				glm::vec3 v2 = physicsObjects[j]->GetVelocity();
				
				// Separate objects after collision.
				/*glm::vec3 depth = physicsObjects[i]->GetBoundingBox()->GetIntersectionDepth(*(physicsObjects[j]->GetBoundingBox()))
								+ glm::vec3(0.02f);
				glm::vec3 sav = glm::abs(v1) + glm::abs(v2) + glm::vec3(0.001f);
				glm::vec3 depth1 = glm::vec3(0.f);
				glm::vec3 depth2 = glm::vec3(0.f);
				if(v1[0] + v1[1] + v1[2] > 0.f)
					depth1 = -1.f * (v1/ glm::abs(v1)) / sav * (depth/2.f);
				if(v2[0] + v2[1] + v2[2] > 0.f)
					depth2 = -1.f * (v2/ glm::abs(v2)) / sav * (depth/2.f);
				physicsObjects[i]->Translate(depth1);
				physicsObjects[j]->Translate(depth2);*/
				
				float m1 = physicsObjects[i]->GetMass();
				float m2 = physicsObjects[j]->GetMass();
				physicsObjects[i]->SetVelocity((m1-m2)/(m1+m2)*v1 + 2*m2/(m1+m2)*v2);
				physicsObjects[j]->SetVelocity((m2-m1)/(m1+m2)*v2 + 2*m1/(m1+m2)*v1);
				printf("PHYSICS WORLD: Collsision Detcted between %d and %d\n", i, j);
			}
		}
	}
}