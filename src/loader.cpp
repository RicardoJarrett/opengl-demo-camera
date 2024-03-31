#include "loader.h"

#include <fstream>
#include <iostream>

#include "stb_image.h"

/*
input	- obj file.
parse	- filepath -> pos, tex, normal, indices arrays
create	- ptni arrays -> ptn + i (combine ptn + create new index)
return	- ptn + i, count
*/

glm::vec3 loader::find_pos_points(lineData currentLine) {
	glm::vec3 tVec;
	std::string item;

	size_t pos = currentLine.pos;
	std::string& line = *(currentLine.line);
	size_t& offset = *(currentLine.offset);

	int index = 0;
	while (pos != std::string::npos) {
		pos = line.find(' ', offset);
		item = (line).substr(offset, pos - offset);
		tVec[index] = std::stof(item);
		offset = pos + 1;
		index += 1;
	}
	return tVec;
}
/*
glm::vec3 loader::find_pos_points(lineData currentLine) {
	glm::vec3 tVec;
	std::string item;
	int index = 0;
	while (currentLine.pos != std::string::npos) {
		currentLine.pos = (*(currentLine.line)).find(' ', *(currentLine.offset));
		item = (*(currentLine.line)).substr(*(currentLine.offset), currentLine.pos - *(currentLine.offset));
		tVec[index] = std::stof(item);
		*(currentLine.offset) = currentLine.pos + 1;
		index += 1;
	}
	return tVec;
}
*/

glm::vec2 loader::find_tex_points(lineData currentLine) {
	glm::vec2 tVec;
	std::string item;
	int index = 0;
	while (currentLine.pos != std::string::npos) {
		currentLine.pos = (*(currentLine.line)).find(' ', *(currentLine.offset));
		item = (*(currentLine.line)).substr(*(currentLine.offset), currentLine.pos - *(currentLine.offset));
		tVec[index] = std::stof(item);
		*(currentLine.offset) = currentLine.pos + 1;
		index += 1;
	}
	return tVec;
}

glm::vec3 loader::find_normal_points(lineData currentLine) {
	glm::vec3 tVec;
	std::string item;
	int index = 0;
	while (currentLine.pos != std::string::npos) {
		currentLine.pos = (*(currentLine.line)).find(' ', *(currentLine.offset));
		item = (*(currentLine.line)).substr(*(currentLine.offset), currentLine.pos - *(currentLine.offset));
		tVec[index] = std::stof(item);
		*(currentLine.offset) = currentLine.pos + 1;
		index += 1;
	}
	return tVec;
}

verti loader::parse_index(lineData currentLine) {
	std::string face;
	int index = 0;

	verti indexVert;
	
	while (currentLine.pos != std::string::npos) {
		currentLine.pos = (*(currentLine.line)).find(' ', *(currentLine.offset));
		face = (*(currentLine.line)).substr(*(currentLine.offset), currentLine.pos - *(currentLine.offset));

		indexVert.position[index] = std::stoi(face.substr(0, face.find('/')));
		face = face.substr(face.find('/') + 1);

		indexVert.tex[index] = std::stoi(face.substr(0, face.find('/')));
		face = face.substr(face.find('/') + 1);

		indexVert.normal[index] = std::stoi(face);
		*(currentLine.offset) = currentLine.pos + 1;
		index += 1;
	}

	return indexVert;
}

void loader::create_object(vtni* loaded_obj, std::string path) {
	parse_file(loaded_obj, path);
}

void loader::parse_file(vtni* dest_obj, std::string path) {
	std::ifstream ifile(path);
	
	if (!ifile.is_open()) {
		std::cout << "Failed to open: " << path << "\n";
	}
	
	std::vector<glm::vec3> p_list, n_list;
	std::vector<glm::vec2> t_list;
	std::vector<verti> i_list;

	std::string line;
	std::string item;

	while (std::getline(ifile, line)) {
		size_t pos = line.find(' ');
		if (pos != std::string::npos) {
			item = line.substr(0, pos);
		}

		size_t offset = pos + 1;
		lineData currentLine = { pos, &line, &offset };
		std::vector<glm::vec3>* list = nullptr;
		if (item == "v") {
			p_list.push_back(find_pos_points(currentLine));
		}
		else if (item == "vn") {
			n_list.push_back(find_normal_points(currentLine));
		}
		else if (item == "vt") {
			t_list.push_back(find_tex_points(currentLine));
		}
		else if (item == "f") {
			i_list.push_back(parse_index(currentLine));
		}
	}
	int vertex_list_size = i_list.size() * 3;
	dest_obj->size = vertex_list_size;
	dest_obj->index_list = (int*)std::calloc(vertex_list_size, sizeof(int));
	dest_obj->vertex_list = (vertexf*)std::calloc(vertex_list_size, sizeof(vertexf));

	int counter = 0;
	for (std::vector<verti>::iterator it = i_list.begin(); it != i_list.end(); it++) {
		verti& index = *it;
		for (int i = 0; i < 3; i++)
		{
			dest_obj->vertex_list[(counter * 3) + i].position[0] = p_list[index.position[i] - 1][0] * 0.5;
			dest_obj->vertex_list[(counter * 3) + i].position[1] = p_list[index.position[i] - 1][1] * 0.5;
			dest_obj->vertex_list[(counter * 3) + i].position[2] = p_list[index.position[i] - 1][2] * 0.5;
			dest_obj->vertex_list[(counter * 3) + i].tex[0] = t_list[index.tex[i] - 1][0];
			dest_obj->vertex_list[(counter * 3) + i].tex[1] = t_list[index.tex[i] - 1][1];
			dest_obj->vertex_list[(counter * 3) + i].normal[0] = n_list[index.normal[i] - 1][0];
			dest_obj->vertex_list[(counter * 3) + i].normal[1] = n_list[index.normal[i] - 1][1];
			dest_obj->vertex_list[(counter * 3) + i].normal[2] = n_list[index.normal[i] - 1][2];
			dest_obj->index_list[(counter * 3) + i] = (counter * 3) + i;
		}
		counter++;
	}
	ifile.close();
}

void loader::load_tex(std::string path, GLuint* texID) {
	glGenTextures(1, texID);
	glBindTexture(GL_TEXTURE_2D, *texID);

	int width, height, channels;

	unsigned char* image =
		stbi_load(path.c_str(), &width, &height, &channels, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	if (image) {
		stbi_image_free(image);

	}
	else {
		std::cout << "Error creating image.\n";
	}
}