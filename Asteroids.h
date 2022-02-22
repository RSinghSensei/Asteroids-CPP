#pragma once
#include "Shapes.h"
#include <glm-0.9.9.8/glm/glm.hpp>
#include "Shader.h"
#include <stdlib.h>
#include <vector>


class Asteroids {
public:

	void AsteroidDraw(GLuint& VAO, Shader ref, GLuint& t1, GLfloat dt);
	void AsteroidCollisionCheck();
	std::vector<glm::vec2>VertexPos();
	void Vposcheck();

	AsteroidShape a1;
	glm::vec3 astpos = glm::vec3(600.0f, 100.0f, 1.0f);
	glm::vec3 astsize = glm::vec3(200.0f, 200.0f, 1.0f);
		
	float x_speed = rand() % 10 + 50;
	float y_speed = rand() % 10 + 50;
	 

	GLfloat astangle = rand() % 25 + 100;

	bool Hit = false;

};