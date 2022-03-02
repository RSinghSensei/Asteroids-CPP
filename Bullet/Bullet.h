#pragma once
#include "../Shapes/Shapes.h"
#include "../Shader/Shader.h"
#include <vector>
#include "../Asteroids/Asteroids.h"
#include <glm-0.9.9.8/glm/glm.hpp>


class Bullet {
public:

	Bullet(const glm::vec3 playerpos, const GLfloat angle);
	~Bullet() = default;

	void BulletDraw(Shader ref, GLuint& t1, GLfloat dt);
	void BulletCollision(std::vector<Asteroids*>& astcheck);
	bool isImpact() const { return Impact; }
	const glm::vec3& getcurrentPos() const { return bulpos; }
	const glm::vec3& getogpos() const { return bulposog; }

	BulletShape b1;	

private:
	GLfloat bulangle = 0.0f;
	glm::vec3 bulpos = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 bulposog = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 Bulletsize = glm::vec3(20.0f, 20.0f, 1.0f);
	GLfloat BulletSpeed = 1500.0f;

	bool Impact = false;
	

};