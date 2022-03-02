#pragma once
#include <glm-0.9.9.8/glm/glm.hpp>
#include "../Shapes/Shapes.h"
#include "../Shader/Shader.h"

struct endGame
{
	endGame() = default;

	void draw(Shader ref, GLuint& t1, GLfloat dt);

	endGameScreen endState;
	glm::vec3 endstatePos{ 0.0f, 0.0f, 0.0f };
	glm::vec3 endstateSize{ 1600.0f, 1200.0f, 1.0f };

};