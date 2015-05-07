#ifndef ShaderProgram_h__
#define ShaderProgram_h__

#include <gl/glew.h>
#include "Shaders/shader.hpp"


class ShaderProgram
{
protected:
	GLuint programID;
public:
	ShaderProgram();
	~ShaderProgram();

	void UseProgram();
	virtual void Initialize();
	virtual void CleanUp();
};

#endif // ShaderProgram_h__