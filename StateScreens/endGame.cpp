#include "endGame.h"

void endGame::draw(Shader ref, GLuint& t1, GLfloat dt)
{
	glBindTexture(GL_TEXTURE_2D, endState.getTexture());
	glBindVertexArray(endState.getVAO());
	glm::mat4 model(1.0f);

	model = glm::translate(model, this->endstatePos);
	model = glm::scale(model, this->endstateSize);

	ref.setUniform(t1, "Transform", model);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}