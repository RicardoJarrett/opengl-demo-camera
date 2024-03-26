#include "mesh.h"

#include <iostream>

mesh::mesh(GLuint id, vtni* data) : meshID(id), vertexBufferID(0), vertexArrayID(0), texID(0), elementBufferID(0), size(0) {
	vtni& _data = *data;
	if (_data.size <= 0) {
		std::cout << "Error: vtni size: " << _data.size << "\n";
		return;
	}
	size = _data.size;
	float* buffer = (float*)std::calloc(_data.size * 8, sizeof(float));
	GLuint* index_buffer = (GLuint*)std::calloc(_data.size, sizeof(GLuint));
	for (int i = 0; i < _data.size; i++) {
		buffer[(i * 8)] = _data.vertex_list[i].position[0];
		buffer[(i * 8) + 1] = _data.vertex_list[i].position[1];
		buffer[(i * 8) + 2] = _data.vertex_list[i].position[2];
		buffer[(i * 8) + 3] = _data.vertex_list[i].tex[0];
		buffer[(i * 8) + 4] = _data.vertex_list[i].tex[1];
		buffer[(i * 8) + 5] = _data.vertex_list[i].normal[0];
		buffer[(i * 8) + 6] = _data.vertex_list[i].normal[1];
		buffer[(i * 8) + 7] = _data.vertex_list[i].normal[2];
		index_buffer[i] = i;

		/*
		std::cout << i << " " << _data.vertex_list[i].position[0] << "," << _data.vertex_list[i].position[1] << "," << _data.vertex_list[i].position[2];
		std::cout << " " << _data.vertex_list[i].tex[0] << "," << _data.vertex_list[i].tex[1];
		std::cout << " " << _data.vertex_list[i].normal[0] << "," << _data.vertex_list[i].normal[1] << "," << _data.vertex_list[i].normal[2] << "\n";
		*/
	}
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, _data.size * 8 * sizeof(float), buffer, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(5 * sizeof(GLfloat)));

	glGenBuffers(1, &elementBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _data.size * sizeof(GLuint), index_buffer, GL_STATIC_DRAW);

	free(buffer);
	free(index_buffer);
}