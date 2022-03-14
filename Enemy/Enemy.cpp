#include "Enemy.h"

void Enemy::draw(Shader ref, GLuint& t1, GLfloat dt)
{
	//glBindTexture(GL_TEXTURE_2D, es.getTexture());
	glBindTexture(GL_TEXTURE_2D, ResourceManager::getInstance()->getTexture("enemyship"));
	glBindVertexArray(es.getVAO());
	glm::mat4 model(1.0f);

	model = glm::translate(model, this->enemyPos);
	model = glm::scale(model, this->enemySize);

	//this->enemyPos.y += this->y_speed * dt * cos(this->enemyAngle);
	if (!arrival)
	{
		this->enemyPos.x += this->x_speed * dt;
	}
	else
	{
		this->enemyPos.y += this->y_speed * dt * cos(this->enemyAngle);
		this->enemyPos.x += this->x_speed * dt * -sin(this->enemyAngle);
	}
	ref.setUniform(t1, "Transform", model);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


}

void Enemy::collisionCheck()
{
	if (!arrival) { return; }
	if (this->enemyPos.x + (this->enemySize.x / 2) <= -805.0f || this->enemyPos.x - (this->enemySize.x / 2) >= 805.0f) {
		this->enemyPos.x *= -0.9f;
	}
	if (this->enemyPos.y + (this->enemySize.y / 2) <= -605.0f || this->enemyPos.y - (this->enemySize.y / 2) >= 605.0f) {
		this->enemyPos.y *= -0.9f;
	}
}

void Enemy::checkArrival()
{
	if (this->enemyPos.x + (this->enemySize.x / 2) >= 0.0f && this->enemyPos.x - (this->enemySize.x / 2) <= 0.0f)
	{
		if (this->enemyPos.y + (this->enemySize.y / 2) >= 0.0f && this->enemyPos.y - (this->enemySize.y / 2) <= 0.0f)
		{
			arrival = true;
			return;
		}
	}

}

std::vector<glm::vec2> Enemy::vertexPos()
{

	std::vector<glm::vec2>v1;
	glm::vec2 aTR = glm::vec2(this->enemyPos.x + (this->enemySize.x / 2), this->enemyPos.y + (this->enemySize.y / 2));
	glm::vec2 aTL = glm::vec2(this->enemyPos.x - (this->enemySize.x / 2), this->enemyPos.y + (this->enemySize.y / 2));
	glm::vec2 aBL = glm::vec2(this->enemyPos.x - (this->enemySize.x / 2), this->enemyPos.y - (this->enemySize.y / 2));
	glm::vec2 aBR = glm::vec2(this->enemyPos.x + (this->enemySize.x / 2), this->enemyPos.y - (this->enemySize.y / 2));
	v1.push_back(aTR);
	v1.push_back(aTL);
	v1.push_back(aBL);
	v1.push_back(aBR);

	return v1;


}