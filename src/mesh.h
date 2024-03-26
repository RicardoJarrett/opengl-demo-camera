#pragma once
#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "utility.h"

class mesh {
public:
	GLuint meshID, vertexBufferID, elementBufferID, texID, vertexArrayID;
	int size;
	mesh(GLuint id, vtni* data);
};