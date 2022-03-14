#include "menuGame.h"

void menuGame::draw(Shader ref, GLuint& t1, GLfloat dt)
{
	//glBindTexture(GL_TEXTURE_2D, m_beginningState.getTexture());
	glBindTexture(GL_TEXTURE_2D, ResourceManager::getInstance()->getTexture("menu"));
	glBindVertexArray(m_beginningState.getVAO());
	glm::mat4 model(1.0f);

	model = glm::translate(model, this->m_beginningStatePos);
	model = glm::scale(model, this->m_beginningStateSize);

	ref.setUniform(t1, "Transform", model);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}