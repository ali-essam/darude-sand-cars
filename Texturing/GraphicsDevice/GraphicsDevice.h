#ifndef GraphicsDevice_h__
#define GraphicsDevice_h__

#include <gl/glew.h>
#include "Shaders/shader.hpp"


class GraphicsDevice
{
	GLuint programID;

	GLuint modelMatrixID;
	GLuint vpMatrixID;
public:
	GraphicsDevice();
	~GraphicsDevice();

	void BindModelMatrix(GLfloat* value);
	void BindVPMatrix(GLfloat* value);
	void BeginDraw();
	void Initialize();
	void CleanUp();
};

#endif // GraphicsDevice_h__