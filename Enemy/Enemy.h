#pragma once
#include <glm-0.9.9.8/glm/glm.hpp>
#include "../Shapes/Shapes.h"
#include "../Shader/Shader.h"
#include <vector>

struct Enemy
{
	Enemy(const glm::vec3& pos): enemyPos(pos) {}

	void draw(Shader ref, GLuint& t1, GLfloat dt);
	std::vector<glm::vec2>vertexPos();
	void collisionCheck();
	void checkArrival();


	enemyShape es;
	glm::vec3 enemyPos;
	glm::vec3 enemySize{ 100.0f, 100.0f, 1.0f };
	float enemyAngle = rand() % 200 + 200;
	float x_speed = rand() % 10 + 200;
	float y_speed = rand() % 10 + 200;
	bool arrival = false;
	bool sound = false;


};