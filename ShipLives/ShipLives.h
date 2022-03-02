#pragma once
#include <glm-0.9.9.8/glm/glm.hpp>
#include "../Shapes/Shapes.h"
#include "../Shader/Shader.h"

struct ShipLives
{
	ShipLives(const glm::vec3& pos):lifePos(pos){}

	void draw(Shader ref, GLuint& t1, GLfloat dt);

	ShipLifeShape slp1;
	glm::vec3 lifePos;
	glm::vec3 lifeScale{ 50.0f, 100.0f, 1.0f };

};