#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Shape{
public:
	Shape();
	~Shape();
public:
	//GLuint bufferint();
	float quad_verts[3 * 4] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int quad_indices[3 * 2] = 
	{
	  0, 1, 3,
	  1, 2, 3
	};
	
	GLuint VAO;
};
