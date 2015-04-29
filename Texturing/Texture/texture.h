#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture
{

public:
	/*unsigned*/ int width, height;
	int numComponents;
	unsigned char * data;
	int texUnit;
	bool loaded;
	void Bind();
	Texture();
	Texture(const std::string& fileName, int texUnit);
	bool LoadFromFile(const std::string& fileName, int texUnit);
	virtual ~Texture();
protected:
private:
	Texture(const Texture& texture) {}
	void operator=(const Texture& texture) {}
	GLuint m_texture;
};

#endif
//GLuint loadBMP_custom(const char * imagepath);