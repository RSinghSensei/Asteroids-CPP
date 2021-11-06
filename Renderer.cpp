#include "Renderer.h"


Renderer::Renderer(){}
Renderer::~Renderer() {}

void Renderer::Draw(GLuint& VAO, Shader ref, GLuint &t1, glm::vec3 &pos, GLfloat angle, glm::vec3 &axis) {
	/*glUseProgram(ShaderProgram);*/
	glBindVertexArray(VAO);	

	glm::mat4 model(1.0f);

	model = glm::translate(model, pos);
	model = glm::rotate(model, angle, axis);
	model = glm::scale(model, glm::vec3(50.0f, 100.0f, 1.0f));
	
	
	

	ref.setUniform(t1, "Transform", model);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}