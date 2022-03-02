#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shape{
public:
	Shape(){}	
	virtual ~Shape() {};

	GLuint testsub(const char* imgSource);
	GLuint getVAO() const { return VAO; }
	GLuint getTexture() const { return texture; }
protected:
	GLuint VAO;
	GLuint texture;
	unsigned int quad_indices[3 * 2] =
	{
	  0, 1, 3,
	  1, 2, 3
	};
};

class AsteroidShape : public Shape
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

	/*unsigned int quad_indices[3 * 2] =
	{
	  0, 1, 3,
	  1, 2, 3
	};

	GLuint VAO;
	GLuint texture;*/

};

class ShipShape : public Shape
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

	//unsigned int quad_indices[3 * 2] =
	//{
	//  0, 1, 3,
	//  1, 2, 3
	//};

	//GLuint VAO;
	//GLuint texture;

};

class BulletShape : public Shape
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

	//unsigned int quad_indices[3 * 2] =
	//{
	//  0, 1, 3,
	//  1, 2, 3
	//};

	//GLuint VAO;
	//GLuint texture;

};

class StarShape : public Shape
{
public:
	StarShape();
	~StarShape();

	float quad_verts[8 * 4] =
	{
		 0.5f,  0.5f, -1.0f, 0.8f, 0.8f, 0.8f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, -1.0f, 0.8f, 0.8f, 0.8f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, -1.0f, 0.8f, 0.8f, 0.8f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, -1.0f, 0.8f, 0.8f, 0.8f, 0.0f, 1.0f  // top left 
	};

	//unsigned int quad_indices[3 * 2] =
	//{
	//  0, 1, 3,
	//  1, 2, 3
	//};

	//GLuint VAO;
	//GLuint texture;

};

class ShipLifeShape : public Shape
{
public:
	ShipLifeShape();
	~ShipLifeShape();

	float quad_verts[8 * 4] =
	{
		 0.5f,  0.5f, 1.0f, 0.8f, 0.8f, 0.8f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 1.0f, 0.8f, 0.8f, 0.8f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 1.0f, 0.8f, 0.8f, 0.8f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 1.0f, 0.8f, 0.8f, 0.8f, 0.0f, 1.0f  // top left 
	};

	//unsigned int quad_indices[3 * 2] =
	//{
	//  0, 1, 3,
	//  1, 2, 3
	//};

	//GLuint VAO;
	//GLuint texture;

};

class enemyShape : public Shape
{
public:
	enemyShape();
	~enemyShape();

	float quad_verts[8 * 4] =
	{
		 0.5f,  0.5f, 1.0f, 0.8f, 0.8f, 0.8f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 1.0f, 0.8f, 0.8f, 0.8f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 1.0f, 0.8f, 0.8f, 0.8f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 1.0f, 0.8f, 0.8f, 0.8f, 0.0f, 1.0f  // top left 
	};

	//unsigned int quad_indices[3 * 2] =
	//{
	//  0, 1, 3,
	//  1, 2, 3
	//};

	//GLuint VAO;
	//GLuint texture;

};

class endGameScreen : public Shape
{
public:
	endGameScreen();
	~endGameScreen();

	float quad_verts[8 * 4] =
	{
		 0.5f,  0.5f, 1.0f, 0.8f, 0.8f, 0.8f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 1.0f, 0.8f, 0.8f, 0.8f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 1.0f, 0.8f, 0.8f, 0.8f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 1.0f, 0.8f, 0.8f, 0.8f, 0.0f, 1.0f  // top left 
	};

	//unsigned int quad_indices[3 * 2] =
	//{
	//  0, 1, 3,
	//  1, 2, 3
	//};

	//GLuint VAO;
	//GLuint texture;

};

class menuScreenImage : public Shape
{
public:
	menuScreenImage();
	~menuScreenImage();

	float quad_verts[8 * 4] =
	{
		 0.5f,  0.5f, 1.0f, 0.8f, 0.8f, 0.8f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 1.0f, 0.8f, 0.8f, 0.8f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 1.0f, 0.8f, 0.8f, 0.8f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 1.0f, 0.8f, 0.8f, 0.8f, 0.0f, 1.0f  // top left 
	};

	//unsigned int quad_indices[3 * 2] =
	//{
	//  0, 1, 3,
	//  1, 2, 3
	//};

	//GLuint VAO;
	//GLuint texture;

};