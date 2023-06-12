#pragma once
#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<GL/glew.h>
#include"VBO.h"

class VAO
{
public:
	unsigned int ID;
	VAO();

	void LinkAttrib(VBO& VBO, unsigned int layout, unsigned int numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};

#endif
