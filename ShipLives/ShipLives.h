#pragma once
#include <glm-0.9.9.8/glm/glm.hpp>
#include "../Shapes/Shapes.h"
#include "../Shader/Shader.h"

struct ShipLives
{
	ShipLives(const glm::vec3& pos):lifePos(pos){}

	void draw(Shader ref, GLuint& t1, GLfloat dt);

	ShipLifeShape slp1;
	glm::vec3 lifePos;
	glm::vec3 lifeScale{ 50.0f, 100.0f, 1.0f };

};

void ShipLives::draw(Shader ref, GLuint& t1, GLfloat dt)
{
	glBindTexture(GL_TEXTURE_2D, slp1.texture);
	glBindVertexArray(slp1.VAO);
	glm::mat4 model(1.0f);

	model = glm::translate(model, this->lifePos);
	model = glm::scale(model, this->lifeScale);


	ref.setUniform(t1, "Transform", model);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


}