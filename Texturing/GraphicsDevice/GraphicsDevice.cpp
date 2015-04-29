#include "GraphicsDevice.h"

GraphicsDevice::GraphicsDevice()
{
}

GraphicsDevice::~GraphicsDevice()
{
}

void GraphicsDevice::Initialize()
{
	programID = LoadShaders( "MainVert.vert", "MainFrag.frag");

	modelMatrixID = glGetUniformLocation(programID, "M");

	vpMatrixID = glGetUniformLocation(programID, "VP");
}

void GraphicsDevice::BindModelMatrix(GLfloat* value)
{
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, value);
}

void GraphicsDevice::BindVPMatrix(GLfloat* value)
{
	glUniformMatrix4fv(vpMatrixID, 1, GL_FALSE, value);
}

void GraphicsDevice::BeginDraw()
{
	glUseProgram(programID);
}

void GraphicsDevice::CleanUp()
{
	glDeleteProgram(programID);
}