#ifndef IBO_CLASS_H
#define IBO_CLASS_H

#include<GL/glew.h>

class IBO
{
public:
	unsigned int ID;
	IBO(unsigned int* indices, GLsizeiptr);

	void Bind();
	void Unbind();
	void Delete();
};

#endif
