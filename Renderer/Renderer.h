#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Shader/Shader.h"
#include "../Shapes/Shapes.h"

class Renderer {
public:
	Renderer();
	~Renderer();
	void Draw(Shader ref, GLuint& t1/*, glm::vec3 &pos, GLfloat angle, glm::vec3 &axis*/);
	void Reset();
	void gameOver();

	ShipShape rec;



	glm::vec3 pos{ 0.0f, 1.0f, 1.0f };
	glm::vec3 axis{ 0.0f, 0.0f, 1.0f };
	GLfloat angle = 0.0f;
	GLfloat velocity = 0.0f;
	GLfloat acceleration = 200.0f;
	bool Engine = false;
	bool respawnInvincibility = false;
	GLfloat refangle = angle;
	std::clock_t startTime;

};


