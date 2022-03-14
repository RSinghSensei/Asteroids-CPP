#pragma once
#include<entt/entt.hpp>
#include <vector>
#include <ctime>
#include "../Components/Components.h"

class SATCollision
{
public:
	SATCollision() = default;
	~SATCollision() = default;

	void update(entt::registry& m_registry, float dt, bool& respawnInvincibility, bool& isgameover, bool& gameactive, std::vector<entt::entity>& m_shiplives, std::clock_t& respawnTimer, int &livesLeft);
	bool SeperatingAxisCollision(const std::vector<glm::vec2>& pol1, const std::vector<glm::vec2>& pol2, const glm::vec2& p1normal1, const glm::vec2& p1normal2, const glm::vec2& p1normal3, const glm::vec2& p1normal4);
	std::pair<float, float> ProjVerts(const std::vector<glm::vec2>& v1, const glm::vec2& axis);
};