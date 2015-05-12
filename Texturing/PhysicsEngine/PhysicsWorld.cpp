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
				if(m1 == 0 || m2 == 0)
				{
					glm::vec3 depth = physicsObjects[i]->GetBoundingBox()->GetIntersectionDepth(*(physicsObjects[j]->GetBoundingBox()))
						+ glm::vec3(0.02f);
					physicsObjects[i]->SetVelocity(glm::vec3(0));
					physicsObjects[j]->SetVelocity(glm::vec3(0));

					glm::vec3 v1n = GetVecDir(physicsObjects[i]->GetBoundingBox()->GetCenter() - physicsObjects[j]->GetBoundingBox()->GetCenter());
					glm::vec3 v2n = GetVecDir(physicsObjects[j]->GetBoundingBox()->GetCenter() - physicsObjects[i]->GetBoundingBox()->GetCenter());
					//glm::vec3 v1n = GetVecDir(v1) * glm::normalize(v1);
					//glm::vec3 v2n = GetVecDir(v2) * glm::normalize(v2);

					if(m1 == 0)
						physicsObjects[j]->Translate(v2n * (depth + glm::vec3(1.f)));
					else
						physicsObjects[i]->Translate(v1n * (depth + glm::vec3(1.f)));
				}
				else
				{
					physicsObjects[i]->SetVelocity((m1-m2)/(m1+m2)*v1 + 2*m2/(m1+m2)*v2);
					physicsObjects[j]->SetVelocity((m2-m1)/(m1+m2)*v2 + 2*m1/(m1+m2)*v1);
				}
				//printf("PHYSICS WORLD: Collsision Detcted between %d and %d\n", i, j);
			}
		}
	}
}

glm::vec3 PhysicsWorld::GetVecDir(glm::vec3 v)
{
	return glm::vec3((v.x==0)?0:v.x/abs(v.x), (v.y==0)?0:v.y/abs(v.y), (v.z==0)?0:v.z/abs(v.z));
}