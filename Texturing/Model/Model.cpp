#include "Model.h"


Model::Model()
{
}


Model::~Model()
{
}

glm::mat4 Model::aiMat4x4ToglmMat4(aiMatrix4x4 aimat)
{
	glm::mat4 gmat;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			// Transpose matrix, as aiMatrix4x4 is column major while opengl is row major.
			gmat[i][j] = aimat[j][i];
		}
	}
	return gmat;
}

std::string Model::GetDirectoryPath(std::string sFilePath)
{
	std::string sDirectory = "";
	for (int i = sFilePath.length(); i >= 0; i--)
	{
		if(sFilePath[i] == '\\' || sFilePath[i] == '/')
		{
			sDirectory = sFilePath.substr(0, i+1);
			break;
		}
	}
	return sDirectory;
}

bool Model::LoadFromFile(std::string modelFileName, bool flipUVs)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(modelFileName.c_str(),
		aiProcess_Triangulate |
		aiProcess_GenSmoothNormals |
		aiProcess_MakeLeftHanded|
		(flipUVs?aiProcess_FlipUVs:0));

	if(!scene){
		printf("ERROR LOADING MODEL: %s\n", importer.GetErrorString());
		return false;
	}

	std::string modelDir = GetDirectoryPath(modelFileName);
	for (int i = 0; i < scene->mNumMaterials; i++)
	{
		textures.push_back(processMaterial(scene->mMaterials[i], modelDir));
	}

	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		meshes.push_back(processMesh(scene->mMeshes[i]));
	}

	rootNode = processNode(scene->mRootNode, 0);
}

Texture* Model::processMaterial(aiMaterial* aimaterial, std::string dir)
{
	Texture* tex = 0;
	aiString path;
	if(aimaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
	{
		std::string texturePath = dir + path.data;
		printf("Loading Texture: %s\n", texturePath.c_str());
		tex = new Texture(texturePath, 0);
	}
	if(!tex || !(tex->loaded))
	{
		// handle default texture.
		printf("Error Loading Texture. Using default texture.\n");
		tex = new Texture("data\\textures\\default.png", 0);
	}
	return tex;
}

ModelMesh* Model::processMesh(aiMesh* aimesh)
{
	ModelMesh* mesh = new ModelMesh();
	for (int i = 0; i < aimesh->mNumVertices; i++)
	{
		aiVector3D vv = aimesh->mVertices[i];
		mesh->VertexData.push_back(glm::vec3(vv.x, vv.y, vv.z));

		if(aimesh->GetNumUVChannels() > 0){
			aiVector3D uvv = aimesh->mTextureCoords[0][i];
			mesh->UVData.push_back(glm::vec2(uvv.x, uvv.y));
		}

		aiVector3D nv = aimesh->mNormals[i];
		mesh->NormalsData.push_back(glm::vec3(nv.x, nv.y, nv.z));
	}

	for (int i = 0; i < aimesh->mNumFaces; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mesh->IndicesData.push_back(aimesh->mFaces[i].mIndices[j]);
		}
	}

	mesh->texture = textures[aimesh->mMaterialIndex];

	return mesh;
}

ModelNode* Model::processNode(aiNode* ainode, ModelNode* parent)
{
	ModelNode* node = new ModelNode();
	node->name = ainode->mName.data;
	node->parent = parent;
	node->transforms = aiMat4x4ToglmMat4(ainode->mTransformation);
	for (int i = 0; i < ainode->mNumMeshes; i++)
	{
		node->meshes.push_back(meshes[ainode->mMeshes[i]]);
	}
	for (int i = 0; i < ainode->mNumChildren; i++)
	{
		node->children.push_back(processNode(ainode->mChildren[i], node));
	}
	return node;
}

void Model::Initialize()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Initialize();
	}
}

void Model::Render(ModelShaderProgram* modelShader, glm::mat4 transformationMatrix)
{
	rootNode->Render(modelShader, transformationMatrix);

	// Render meshes ignoring nodes structure
	/*for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Render(graphicsDevice);
	}*/
}

void Model::Render(ModelShaderProgram* modelShader)
{
	rootNode->Render(modelShader, glm::mat4(1.0f));
}


void Model::Cleanup()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Cleanup();
	}
	for (int i = 0; i < textures.size(); i++)
	{
		delete textures[i];
	}
}


std::vector<glm::vec3> Model::GetAllVerticies()
{
	std::vector<glm::vec3> verts;
	for (int i = 0; i < meshes.size(); i++)
	{
		for (int j = 0; j < meshes[i]->VertexData.size(); j++)
		{
			verts.push_back(meshes[i]->VertexData[j]);
		}
	}
	return verts;
}

ModelNode* Model::FindNode(std::string name)
{
	return rootNode->FindNode(name);
}