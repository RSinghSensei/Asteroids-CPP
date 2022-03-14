#pragma once
#include <glm-0.9.9.8/glm/glm.hpp>
#include "../Shapes/Shapes.h"
#include "../Shader/Shader.h"
#include "../ResourceManager/ResourceManager.h"

struct menuGame
{
	menuGame() = default;

	void draw(Shader ref, GLuint& t1, GLfloat dt);

	menuScreenImage m_beginningState;
	glm::vec3 m_beginningStatePos{ 0.0f, 0.0f, 0.0f };
	glm::vec3 m_beginningStateSize{ 1600.0f, 1200.0f, 1.0f };

};
