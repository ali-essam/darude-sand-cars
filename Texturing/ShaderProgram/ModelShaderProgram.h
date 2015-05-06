#ifndef ModelShaderProgram_h__
#define ModelShaderProgram_h__

#include <gl/glew.h>
#include "Shaders/shader.hpp"
#include "ShaderProgram.h"


class ModelShaderProgram : public ShaderProgram
{
protected:
	GLuint modelMatrixID;
	GLuint vpMatrixID;
public:
	ModelShaderProgram();
	~ModelShaderProgram();

	virtual void BindModelMatrix(GLfloat* value);
	virtual void BindVPMatrix(GLfloat* value);

};

#endif // ModelShaderProgram_h__