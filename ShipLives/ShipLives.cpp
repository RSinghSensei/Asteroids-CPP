#include "ShipLives.h"

void ShipLives::draw(Shader ref, GLuint& t1, GLfloat dt)
{
	glBindTexture(GL_TEXTURE_2D, slp1.getTexture());
	glBindVertexArray(slp1.getVAO());
	glm::mat4 model(1.0f);

	model = glm::translate(model, this->lifePos);
	model = glm::scale(model, this->lifeScale);


	ref.setUniform(t1, "Transform", model);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


}