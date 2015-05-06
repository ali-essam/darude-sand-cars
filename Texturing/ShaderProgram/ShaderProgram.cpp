#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::UseProgram()
{
	glUseProgram(programID);
}

void ShaderProgram::Initialize()
{
}

void ShaderProgram::CleanUp()
{
}