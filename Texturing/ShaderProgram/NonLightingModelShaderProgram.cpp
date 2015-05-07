#include "NonLightingModelShaderProgram.h"

NonLightingModelShaderProgram::NonLightingModelShaderProgram()
{

}

NonLightingModelShaderProgram::~NonLightingModelShaderProgram()
{

}

void NonLightingModelShaderProgram::Initialize()
{
	programID = LoadShaders( "GLSLShaders\\MainVert.vert", "GLSLShaders\\MainFrag.frag");
	modelMatrixID = glGetUniformLocation(programID, "M");
	vpMatrixID = glGetUniformLocation(programID, "VP");
}

void NonLightingModelShaderProgram::BindModelMatrix(GLfloat* value)
{
		glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, value);
}

void NonLightingModelShaderProgram::BindVPMatrix(GLfloat* value)
{
		glUniformMatrix4fv(vpMatrixID, 1, GL_FALSE, value);
}

void NonLightingModelShaderProgram::CleanUp()
{
		glDeleteProgram(programID);
}