#include "utility.h"

std::string vertexf::string() {
	std::string return_string = "[" + std::to_string(position[0]) + "," + std::to_string(position[1]) + "," + std::to_string(position[2]) + "] ";
	return_string += "[" + std::to_string(tex[0]) + "," + std::to_string(tex[1]) + "] ";
	return_string += "[" + std::to_string(normal[0]) + "," + std::to_string(normal[1]) + "," + std::to_string(normal[2]) + "]";
	return return_string;
}

std::string vtni::string() {
	std::string return_string = "";
	for (int i = 0; i < size; i++) {
		return_string += vertex_list[i].string() + "\n";
	}
	return return_string;
}

void vtni::cleanup() {
	free(this);
}

rts_transformation::rts_transformation(glm::mat4 r, glm::mat4 t, glm::mat4 s) {
	rotation = r;
	translation = t;
	scale = s;
}

rts_transformation::rts_transformation() {
	rotation = glm::mat4(1.0f);
	translation = glm::mat4(1.0f);
	scale = glm::mat4(1.0f);
}