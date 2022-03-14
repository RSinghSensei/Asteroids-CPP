#include "Renderer.h"


Renderer::Renderer(){}
Renderer::~Renderer() {}

void Renderer::Draw(Shader ref, GLuint &t1/*, glm::vec3 &pos, GLfloat angle, glm::vec3 &axis*/) {
	/*glUseProgram(ShaderProgram);*/
	//glBindTexture(GL_TEXTURE_2D, rec.getTexture());
	glBindTexture(GL_TEXTURE_2D, ResourceManager::getInstance()->getTexture("ship"));
	glBindVertexArray(rec.getVAO());	

	glm::mat4 model(1.0f);

	model = glm::translate(model, pos);
	model = glm::rotate(model, angle, axis);
	model = glm::scale(model, glm::vec3(50.0f, 100.0f, 1.0f));
	
	// Vertices of player

	ref.setUniform(t1, "Transform", model);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer::Reset()
{
	pos = glm::vec3(0.0f, 1.0f, 1.0f);
	axis = glm::vec3(0.0f, 0.0f, 1.0f);
	angle = 0.0f;
	velocity = 0.0f;
	respawnInvincibility = true;
}

void Renderer::gameOver()
{
	delete this;
}