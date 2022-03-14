#pragma once
#include <glm-0.9.9.8/glm/glm.hpp>
#include "../Shapes/Shapes.h"
#include "../Shader/Shader.h"
#include "../ResourceManager/ResourceManager.h"

struct Planet
{
	Planet(const glm::vec3& pos) : planetpos(pos){}
	Planet() = default;

	void draw(Shader ref, GLuint& t1, GLfloat dt);

	StarShape p1;
	glm::vec3 planetpos;
	glm::vec3 planetSize{ 300.0f, 300.0f, 1.0f };
};
