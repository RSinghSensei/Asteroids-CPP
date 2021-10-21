#pragma once
#include "Shapes.h"
#include <glm-0.9.9.8/glm/glm.hpp>
#include "Shader.h"
#include <stdlib.h>


class Asteroids {
public:
	void AsteroidDraw(GLuint& VAO, Shader ref, GLuint& t1, GLfloat dt);
	void AsteroidCollisionCheck();

	Shape a1;
	glm::vec3 astpos = glm::vec3(10.0f, 10.0f, 1.0f);
	glm::vec3 astsize = glm::vec3(8.0f, 8.0f, 1.0f);

	float x_speed = rand() % 5 + 5;
	float y_speed = rand() % 5 + 2;
	 

	GLfloat astangle = rand() % 25 + 10;
};