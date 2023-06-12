#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<GL/glew.h>

class VBO
{
public:
	unsigned int ID;
	VBO(float* vertices, GLsizeiptr);

	void Bind();
	void Unbind();
	void Delete();
};

#endif
