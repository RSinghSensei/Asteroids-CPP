#include "Planet.h"

void Planet::draw(Shader ref, GLuint& t1, GLfloat dt)
{
	//glBindTexture(GL_TEXTURE_2D, p1.getTexture());
	glBindTexture(GL_TEXTURE_2D, ResourceManager::getInstance()->getTexture("planet"));
	glBindVertexArray(p1.getVAO());
	glm::mat4 model(1.0f);

	model = glm::translate(model, this->planetpos);
	model = glm::rotate(model, 0.0f, glm::vec3{ 0.0f, 0.0f, 1.0f });
	model = glm::scale(model, this->planetSize);


	ref.setUniform(t1, "Transform", model);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}