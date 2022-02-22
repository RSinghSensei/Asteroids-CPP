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
	void Draw(GLuint &VAO, Shader ref, GLuint& t1, glm::vec3 &pos, GLfloat angle, glm::vec3 &axis);

	ShipShape rec;

};


