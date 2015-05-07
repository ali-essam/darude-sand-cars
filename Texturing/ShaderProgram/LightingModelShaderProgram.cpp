#include "LightingModelShaderProgram.h"

LightingModelShaderProgram::LightingModelShaderProgram()
{

}

LightingModelShaderProgram::~LightingModelShaderProgram()
{

}

void LightingModelShaderProgram::Initialize()
{
	programID = LoadShaders( "GLSLShaders\\LightingVert.vert", "GLSLShaders\\LightingFrag.frag");
	modelMatrixID = glGetUniformLocation(programID, "M");
	vpMatrixID = glGetUniformLocation(programID, "VP");
	ambientLightColorID = glGetUniformLocation(programID, "ambientLightColor");
	directionalLightColorID = glGetUniformLocation(programID, "directionalLightColor");
	directionalLightDirectionID = glGetUniformLocation(programID, "directionalLightDirection");
}

void LightingModelShaderProgram::BindModelMatrix(GLfloat* value)
{
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, value);
}

void LightingModelShaderProgram::BindVPMatrix(GLfloat* value)
{
	glUniformMatrix4fv(vpMatrixID, 1, GL_FALSE, value);
}

void LightingModelShaderProgram::SetDirectionalLight(DirectionalLightSource& lightSource)
{
	this->UseProgram();
	glm::vec3 directionalLightColor = lightSource.GetColor();
	glUniform3fv(directionalLightColorID, 1, &directionalLightColor[0]);
	glm::vec3 directionalLightDirection = lightSource.GetDirection();
	glUniform3fv(directionalLightDirectionID, 1, &directionalLightDirection[0]);
	glm::vec3 ambientLightColor = glm::vec3(0.1f, 0.1f, 0.1f);
	glUniform3fv(ambientLightColorID, 1, &ambientLightColor[0]);
}

void LightingModelShaderProgram::CleanUp()
{
	glDeleteProgram(programID);
}