#include "LightingModelShaderProgram.h"

LightingModelShaderProgram::LightingModelShaderProgram()
{

}

LightingModelShaderProgram::~LightingModelShaderProgram()
{

}

void LightingModelShaderProgram::Initialize()
{
	programID = LoadShaders( "GLSLShaders\\MainVert.vert", "GLSLShaders\\MainFrag.frag");
	modelMatrixID = glGetUniformLocation(programID, "M");
	vpMatrixID = glGetUniformLocation(programID, "VP");
}

void LightingModelShaderProgram::BindModelMatrix(GLfloat* value)
{
			glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, value);
}

void LightingModelShaderProgram::BindVPMatrix(GLfloat* value)
{
			glUniformMatrix4fv(vpMatrixID, 1, GL_FALSE, value);
}

void LightingModelShaderProgram::SetDirectionalLight(DirectionalLightSource * lightSource)
{

}

void LightingModelShaderProgram::CleanUp()
{
			glDeleteProgram(programID);
}