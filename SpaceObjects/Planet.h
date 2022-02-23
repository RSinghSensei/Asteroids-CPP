#pragma once
#include <glm-0.9.9.8/glm/glm.hpp>
#include "../Shapes/Shapes.h"
#include "../Shader/Shader.h"

struct Planet
{
	Planet(const glm::vec3& pos) : planetpos(pos){}

	void draw(Shader ref, GLuint& t1, GLfloat dt);

	StarShape p1;
	glm::vec3 planetpos;
	glm::vec3 planetSize{ 300.0f, 300.0f, 1.0f };
};

void Planet::draw(Shader ref, GLuint& t1, GLfloat dt)
{
	glBindTexture(GL_TEXTURE_2D, p1.texture);
	glBindVertexArray(p1.VAO);
	glm::mat4 model(1.0f);

	model = glm::translate(model, this->planetpos);
	model = glm::scale(model, this->planetSize);


	ref.setUniform(t1, "Transform", model);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}