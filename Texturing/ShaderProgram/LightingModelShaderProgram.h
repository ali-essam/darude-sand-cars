#ifndef LightingModelShaderProgram_h__
#define LightingModelShaderProgram_h__

#include <gl/glew.h>
#include "Shaders/shader.hpp"
#include "ModelShaderProgram.h"
#include "Lighting\DirectionalLightSource.h"

class LightingModelShaderProgram : public ModelShaderProgram
{
public:
	LightingModelShaderProgram();
	~LightingModelShaderProgram();

	void Initialize();
	void CleanUp();
	
	void BindModelMatrix(GLfloat* value);
	void BindVPMatrix(GLfloat* value);

	void SetDirectionalLight(DirectionalLightSource * lightSource);
};

#endif // LightingModelShaderProgram_h__