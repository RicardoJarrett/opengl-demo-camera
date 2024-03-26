#pragma once
#include <vector>
#include <string>
#include <map>
#include <ostream>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "utility.h"

namespace loader {
	void create_object(vtni* loaded_obj, std::string path);
	void parse_file(vtni* dest_obj, std::string path);
	void load_tex(std::string path, GLuint* texID);

	glm::vec3 find_pos_points(lineData currentLine);
	glm::vec2 find_tex_points(lineData currentLine);
	glm::vec3 find_normal_points(lineData currentLine);
	verti parse_index(lineData currentLine);
};