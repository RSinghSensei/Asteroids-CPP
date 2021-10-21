#include "Asteroids.h"

void Asteroids::AsteroidDraw(GLuint& VAO, Shader ref, GLuint& t1, GLfloat dt) {
	glBindVertexArray(VAO);

	glm::mat4 model(1.0f);

	model = glm::translate(model, this->astpos);
	model = glm::scale(model, this->astsize);


	this->astpos.y += this->y_speed * dt * cos(this->astangle);
	this->astpos.x += this->x_speed * dt * -sin(this->astangle);


	ref.setUniform(t1, "Transform", model);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

void Asteroids::AsteroidCollisionCheck() {
	// Collision check

	if (this->astpos.x + (this->astsize.x / 2) <= -20.0f || this->astpos.x - (this->astsize.x / 2) >= 20.0f) {
		std::cout << "Asteroid Collision" << std::endl;
		this->astpos.x *= -1;
		
	}

	if (this->astpos.y + (this->astsize.y / 2) <= -20.0f || this->astpos.y - (this->astsize.y / 2) >= 20.0f) {
		std::cout << "Asteroid Collision" << std::endl;
		this->astpos.y *= -1;
	}

}