#pragma once
#include "mesh.h"

struct model{
	GLuint model_id, mesh_id, texture_id;
	mesh* meshp;

	model();
	model(GLuint _model_id, GLuint _mesh_id, GLuint _texture_id, mesh* _meshp);
	void bind(GLuint shader_id);
};

struct model_instance {
	model* model_p;
	GLuint shader_id;
	glm::mat4 rotation, translation, scale;
	bool draw_enabled;

	model_instance();
	model_instance(model* _model_p, GLuint _shader_id, bool _draw_enabled);

	glm::mat4 get_local_transform();

	void local_rotate(glm::vec3 angles);
	void local_translate(glm::vec3 trans);
	void local_scale(glm::vec3 scale);

	void render(glm::mat4 cam_trans);
};