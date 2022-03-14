#pragma once
#include <glm-0.9.9.8/glm/glm.hpp>
#include "../ResourceManager/ResourceManager.h"

//struct BulletComponent {};

//struct AsteroidComponent {};

struct TransformComponent 
{
	TransformComponent(const glm::vec3& pos, const glm::vec3& size, float angle, const std::string& textureUID)
	{
		m_pos = pos;
		m_size = size;
		m_angle = angle;
		m_texID = ResourceManager::getInstance()->getTexture(textureUID);


		glGenVertexArrays(1, &VAO);
		GLuint VBO, EBO;

		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quad_verts), quad_verts, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad_indices), quad_indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		//texture = testsub(".\\Assets\\Asteroid.png");

		//texture = testsub("asteroids");

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	glm::vec3 m_pos;
	glm::vec3 m_size;
	float m_angle;
	GLuint m_texID;
	GLuint VAO;

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
};

struct PlayerComponent
{
	PlayerComponent() {}

	float m_acceleration = 200.0f;
	float refangle = 0.0f;
	float m_velocity = 0.0f;
	bool isW = false;
};

struct RigidBodyComponent 
{
	RigidBodyComponent(const glm::vec3& velocity) : m_velocity(velocity) {}
	//float m_velocity;
	glm::vec3 m_velocity;
};

struct SpriteComponent 
{
	SpriteComponent(GLuint texID) : m_texID(texID) {}

	GLuint m_texID;
};

struct AsteroidComponent
{
	AsteroidComponent() = default;
	bool astimpact = false;
};

struct BulletComponent
{
	BulletComponent(const glm::vec3& bulletoriginalpos) : m_bulletoriginalpos(bulletoriginalpos) {}
	glm::vec3 m_bulletoriginalpos;
	bool impact = false;

};
//struct EnemyComponent {};

/*
void renderSystem(registry*)
{
	resource manager gets shader program, or shader program already available
	We require shader, vertex array object, and texture
	Transform component will supply pos, size, and rotation
	Sprite component will provide texture ID?

	registry gets both components
	instantaite model matrix
	model translation, rotation, scale 
	set uniform Transform matrix
	Draw elements
	Unbind vertex array object

}
How would we create the object?
Right now we create individual shape objects within each class
Do we keep that heirarchy?
Shape Component and System?
System only called when we need it, not every frame


How would we generate textures in the first place?

ResourceManager instantiates textures, we get the texture, feed it into sprite component?
Sprite Component 



CollisionSystem


*/