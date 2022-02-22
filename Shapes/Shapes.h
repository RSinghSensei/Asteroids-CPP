#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//class Shape{
//public:
//	Shape();
//	~Shape();
//
//	//GLuint bufferint();
//	float quad_verts[3 * 4] = 
//{
//	 0.5f,  0.5f, 0.0f,  // top right
//	 0.5f, -0.5f, 0.0f,  // bottom right
//	-0.5f, -0.5f, 0.0f,  // bottom left
//	-0.5f,  0.5f, 0.0f   // top left 
//	};
//
//	float colorArr[4 * 3] =
//	{
//		0.8f, 0.8f, 0.8f,
//		0.8f, 0.8f, 0.8f,
//		0.8f, 0.8f, 0.8f,
//		0.8f, 0.8f, 0.8f
//	};
//
//	float altcolorArr[4 * 3] =
//	{
//		0.1f, 0.5f, 1.0f,
//		0.1f, 0.5f, 1.0f,
//		0.1f, 0.5f, 1.0f,
//		0.1f, 0.5f, 1.0f
//	};
//
//	unsigned int quad_indices[3 * 2] = 
//	{
//	  0, 1, 3,
//	  1, 2, 3
//	};
//	
//	GLuint VAO;
//
//};

class AsteroidShape
{
public:
	AsteroidShape();
	~AsteroidShape();

	float quad_verts[8 * 4] =
	{
		 0.5f,  0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 0.0f, 1.0f  // top left 
	};

	unsigned int quad_indices[3 * 2] =
	{
	  0, 1, 3,
	  1, 2, 3
	};

	GLuint VAO;
	GLuint texture;

};

class ShipShape
{
public:
	ShipShape();
	~ShipShape();

	float quad_verts[8 * 4] =
	{
		 0.5f,  0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 0.0f, 1.0f  // top left 
	};

	unsigned int quad_indices[3 * 2] =
	{
	  0, 1, 3,
	  1, 2, 3
	};

	GLuint VAO;
	GLuint texture;

};

class BulletShape
{
public:
	BulletShape();
	~BulletShape();

	float quad_verts[8 * 4] =
	{
		 0.5f,  0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 0.0f, 1.0f  // top left 
	};

	unsigned int quad_indices[3 * 2] =
	{
	  0, 1, 3,
	  1, 2, 3
	};

	GLuint VAO;
	GLuint texture;

};
