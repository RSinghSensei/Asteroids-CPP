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

	if (this->astpos.x + (this->astsize.x / 2) <= -800.0f || this->astpos.x - (this->astsize.x / 2) >= 800.0f) {
		this->astpos.x *= -1;
		std::cout << "Buffer Zone" << std::endl;
	}
	if (this->astpos.y + (this->astsize.y / 2) <= -600.0f || this->astpos.y - (this->astsize.y / 2) >= 600.0f) {
		this->astpos.y *= -1;
		std::cout << "Buffer Zone" << std::endl;
	}

}

std::vector<glm::vec2>Asteroids::VertexPos() {
	std::vector<glm::vec2>v1;
	glm::vec2 aTR = glm::vec2(this->astpos.x + (this->astsize.x / 2), this->astpos.y + (this->astsize.y / 2));
	glm::vec2 aTL = glm::vec2(this->astpos.x - (this->astsize.x / 2), this->astpos.y + (this->astsize.y / 2));
	glm::vec2 aBL = glm::vec2(this->astpos.x - (this->astsize.x / 2), this->astpos.y - (this->astsize.y / 2));
	glm::vec2 aBR = glm::vec2(this->astpos.x + (this->astsize.x / 2), this->astpos.y - (this->astsize.y / 2));
	v1.push_back(aTR);
	v1.push_back(aTL);
	v1.push_back(aBL);
	v1.push_back(aBR);

	//std::cout << this->astpos.x - (this->astsize.x / 2) << " ";
	//std::cout << (this->astpos.y + (this->astsize.y / 2)) << std::endl;
	//std::cout << this->astpos.x + (this->astsize.x / 2) << " ";
	//std::cout << this->astpos.y + (this->astsize.y / 2) << std::endl;
	//std::cout << this->astpos.x - (this->astsize.x / 2) << " ";
	//std::cout << this->astpos.y - (this->astsize.y / 2) << std::endl;
	//std::cout << this->astpos.x + (this->astsize.x / 2) << " ";
	//std::cout << this->astpos.y - (this->astsize.y / 2) << std::endl;

	return v1;
}

void Asteroids::Vposcheck() {

}