#include "demo.h"

#include <iostream>

#include "utility.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>

Demo::Demo(GLFWwindow* _window) {
	window = _window;
	uniTrans = 0;
	cube_mesh = nullptr;
	cube_model = model();
	cube_count = 256;
}

Demo::~Demo() {

}

const char* vertex_shader =
"#version 330 core\n"
"layout(location = 0) in vec3 pos;"
"layout(location = 1) in vec2 tex;"
"layout(location = 2) in vec3 normal;"
"out vec2 v_texCoords;"
//"uniform mat4 trans;"
"uniform mat4 model;"
"uniform mat4 view;"
"uniform mat4 projection;"
"void main(){"
"  v_texCoords = tex;"
//"  gl_Position = trans * vec4(pos, 1.0);"
"  gl_Position = model * view * projection * vec4(pos, 1.0);"
"}";

const char* fragment_shader =
"#version 330 core\n"
"in vec2 v_texCoords;"
"uniform sampler2D intexture;"
"layout(location = 0) out vec4 frag_colour;"
"void main(){"
//"  frag_colour = vec4(1.0, 1.0, 1.0, 1.0);"
"  frag_colour = texture(intexture, v_texCoords);"
"}";

void create_shaders(GLuint* shader_programme) {
	*shader_programme = glCreateProgram();
	
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	*shader_programme = glCreateProgram();
	glAttachShader(*shader_programme, fs);
	glAttachShader(*shader_programme, vs);
	glBindAttribLocation(*shader_programme, 0, "pos");
	glBindAttribLocation(*shader_programme, 1, "tex");
	glBindAttribLocation(*shader_programme, 2, "normal");
	glLinkProgram(*shader_programme);

	GLint testVal;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &testVal);
	if (testVal == GL_FALSE)
	{
		char infolog[1024];
		glGetShaderInfoLog(vs, 1024, NULL, infolog);
		printf("The vertex shader failed to compile with the error:\n");
		printf(infolog);
	}
	glGetShaderiv(fs, GL_COMPILE_STATUS, &testVal);
	if (testVal == GL_FALSE)
	{
		char infolog[1024];
		glGetShaderInfoLog(fs, 1024, NULL, infolog);
		printf("The fragment shader failed to compile with the error:\n");
		printf(infolog);
	}
}

int Demo::load_assets() {
	GLuint shader_programme;
	create_shaders(&shader_programme);
	glUseProgram(shader_programme);
	glUniform1i(glGetUniformLocation(shader_programme, "intexture"), 0);
	
	std::string texPath = "assets\\cube.png";
	GLuint texID = 0;
	loader::load_tex(texPath, &texID);

	std::string objPath = "assets\\cube.obj";
	vtni cube_vtni;
	loader::create_object(&cube_vtni, objPath);

	GLuint mesh_id = 0;
	cube_mesh = new mesh(mesh_id, &cube_vtni);

	GLuint model_id = 0;
	cube_model = {model_id, mesh_id, texID, cube_mesh };
	for (int i = 0; i < cube_count; i++) {
		model_instance* tInstance = nullptr;
		tInstance = new model_instance(&cube_model, shader_programme, true);
		instances.push_back(tInstance);
		rotations.push_back(glm::vec3(glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f)));
		translations.push_back(glm::vec3(glm::linearRand(0.0f, 0.003f), glm::linearRand(0.0f, 0.003f), 0.0f));
		tInstance->local_scale(glm::vec3(glm::linearRand(0.0f, 0.05f)));
		tInstance->local_translate(glm::vec3(glm::linearRand(-0.75f, 0.75f), glm::linearRand(-0.75f, 0.75f), 0.0f));
	}

	return 0;
}

float x_bounce = 0.0f;
float y_bounce = 0.0f;
float x_speed = 0.1f;
float y_speed = 0.2f;
int x_dir = 1;
int y_dir = 1;

void Demo::move_cubes() {
	if ((x_bounce >= 100.0f) || (x_bounce <= -100.0f)) {
		x_dir *= -1;
	}
	if ((y_bounce >= 100.0f) || (y_bounce <= -100.0f)) {
		y_dir *= -1;
	}
	x_bounce += x_speed * x_dir;
	y_bounce += y_speed * y_dir;
	for (int i = 0; i < cube_count; i++) {
		instances[i]->local_rotate(rotations[i]);
		glm::vec3 trans = { translations[i].x * x_dir, translations[i].y * y_dir, 0.0 };
		instances[i]->local_translate(trans);
	}
}

int Demo::run() {
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		move_cubes();
		for (int i = 0; i < cube_count; i++) {
			instances[i]->render();
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}