#include "Level.h"

Level::Level():cellSize(150.f)
{
}

Level::~Level()
{
}

void Level::Update(double dt)
{

}

void Level::Render(ModelShaderProgram* modelShader)
{
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			int texi = levelMat[r][c] - '0';
			cellMesh->texture = textures[texi];
			glm::mat4 m = glm::translate(c * cellSize, 0.f, r*cellSize);
			modelShader->BindModelMatrix(&m[0][0]);
			cellMesh->Render();
		}
	}
}

void Level::Initialize()
{
	cellMesh = new ModelMesh();
	cellMesh->VertexData.push_back(glm::vec3(-cellSize/2.f, 0.0f, -cellSize/2.f));
	cellMesh->VertexData.push_back(glm::vec3(-cellSize/2.f, 0.0f, cellSize/2.f));
	cellMesh->VertexData.push_back(glm::vec3(cellSize/2.f, 0.0f, -cellSize/2.f));
	cellMesh->VertexData.push_back(glm::vec3(cellSize/2.f, 0.0f, cellSize/2.f));

	cellMesh->IndicesData.push_back(0);
	cellMesh->IndicesData.push_back(1);
	cellMesh->IndicesData.push_back(2);
	cellMesh->IndicesData.push_back(1);
	cellMesh->IndicesData.push_back(2);
	cellMesh->IndicesData.push_back(3);

	cellMesh->UVData.push_back(glm::vec2(0.0f, 0.0f));
	cellMesh->UVData.push_back(glm::vec2(0.0f, 1.0f));
	cellMesh->UVData.push_back(glm::vec2(1.0f, 0.0f));
	cellMesh->UVData.push_back(glm::vec2(1.0f, 1.0f));

	cellMesh->NormalsData.assign(4, glm::vec3(0.0, 1.0, 0.0));

	cellMesh->Initialize();
}

void Level::LoadFromFile(std::string path)
{
	std::ifstream fs(path + "data.txt");
	fs >> height;
	fs >> width;
	std::string row;
	for (int i = 0; i < height; i++)
	{
		fs >> row;
		levelMat.push_back(row);
		printf("%s\n", row.c_str());
	}

	for (int i = 0; i <= 6; i++)
	{
		std::string texPath = path + (char)(i+'0') + ".png";
		textures[i] = new Texture(texPath.c_str(), 0);
	}

	fs >> startR >> startC;

	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			if(levelMat[r][c] == '0')
			{
				glm::vec3 pos(c * cellSize, cellSize/2.f, r*cellSize);
				AABoundingBox* boundingBox = new AABoundingBox(pos, glm::vec3(cellSize));
				RigidBody* collider = new RigidBody();
				collider->SetBoundingBox(boundingBox);
				collider->SetPosition(pos);
				collider->SetMass(0);
				colliders.push_back(collider);
			}
		}
	}

	Initialize();
}

std::vector<PhysicsObject*> Level::GetPhysicsObjects()
{
	return colliders;
}

glm::vec3 Level::GetStartPosition()
{
	return glm::vec3(startC * cellSize, 0.f, startR*cellSize);
}