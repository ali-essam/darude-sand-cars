#ifndef NonLightingModelShaderProgram_h__
#define NonLightingModelShaderProgram_h__

#include <gl/glew.h>
#include "Shaders/shader.hpp"
#include "ModelShaderProgram.h"

class NonLightingModelShaderProgram : public ModelShaderProgram
{
public:
	NonLightingModelShaderProgram();
	~NonLightingModelShaderProgram();

	void Initialize();
	void CleanUp();
	
	void BindModelMatrix(GLfloat* value);
	void BindVPMatrix(GLfloat* value);

};

#endif // NonLightingModelShaderProgram_h__