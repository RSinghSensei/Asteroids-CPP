#include "SATCollision.h"

void SATCollision::update(entt::registry &m_registry, float dt, bool& respawnInvincibility, bool& isgameover, bool& gameactive,std::vector<entt::entity>& m_shiplives, std::clock_t& respawnTimer, int &livesLeft)
{
	if (!respawnInvincibility && !gameactive)
	{
		auto playerview = m_registry.view<TransformComponent, RigidBodyComponent, PlayerComponent>();
		auto asteroidview = m_registry.view<TransformComponent, RigidBodyComponent, AsteroidComponent>();
		for (auto& entity : playerview)
		{
			const auto& r1 = playerview.get<TransformComponent>(entity);
			std::vector<glm::vec2>player_vert_coords;
			glm::vec2 TR = glm::vec2((r1.m_pos.x + (25.0f * cos(r1.m_angle)) - (50.0f * sin(r1.m_angle))), (r1.m_pos.y + (25.0f * sin(r1.m_angle)) + (50.0f * cos(r1.m_angle))));
			glm::vec2 TL = glm::vec2((r1.m_pos.x - (25.0f * cos(r1.m_angle)) - (50.0f * sin(r1.m_angle))), (r1.m_pos.y - (25.0f * sin(r1.m_angle)) + (50.0f * cos(r1.m_angle))));
			glm::vec2 BL = glm::vec2((r1.m_pos.x - (25.0f * cos(r1.m_angle)) + (50.0f * sin(r1.m_angle))), (r1.m_pos.y - (25.0f * sin(r1.m_angle)) - (50.0f * cos(r1.m_angle))));
			glm::vec2 BR = glm::vec2((r1.m_pos.x + (25.0f * cos(r1.m_angle)) + (50.0f * sin(r1.m_angle))), (r1.m_pos.y + (25.0f * sin(r1.m_angle)) - (50.0f * cos(r1.m_angle))));
			player_vert_coords.push_back(TR);
			player_vert_coords.push_back(TL);
			player_vert_coords.push_back(BL);
			player_vert_coords.push_back(BR);
			glm::vec2 edge1 = TL - TR;
			glm::vec2 edge2 = BL - TL;
			glm::vec2 edge3 = BR - BL;
			glm::vec2 edge4 = TR - BR;
			glm::vec2 normal1 = glm::vec2(edge1.y, -edge1.x);
			glm::vec2 normal2 = glm::vec2(edge2.y, -edge2.x);
			glm::vec2 normal3 = glm::vec2(edge3.y, -edge3.x);
			glm::vec2 normal4 = glm::vec2(edge4.y, -edge4.x);
			for (auto& astentity : asteroidview)
			{
				const auto& ast = asteroidview.get<TransformComponent>(astentity);
				std::vector<glm::vec2>v1;
				glm::vec2 aTR = glm::vec2(ast.m_pos.x + (ast.m_size.x / 2), ast.m_pos.y + (ast.m_size.y / 2));
				glm::vec2 aTL = glm::vec2(ast.m_pos.x - (ast.m_size.x / 2), ast.m_pos.y + (ast.m_size.y / 2));
				glm::vec2 aBL = glm::vec2(ast.m_pos.x - (ast.m_size.x / 2), ast.m_pos.y - (ast.m_size.y / 2));
				glm::vec2 aBR = glm::vec2(ast.m_pos.x + (ast.m_size.x / 2), ast.m_pos.y - (ast.m_size.y / 2));
				v1.push_back(aTR);
				v1.push_back(aTL);
				v1.push_back(aBL);
				v1.push_back(aBR);
				if (SeperatingAxisCollision(player_vert_coords, v1, normal1, normal2, normal3, normal4))
				{
					std::cout << "SAT Collision Detected 1" << std::endl;
					livesLeft -= 1;
					if (livesLeft <= 0) { isgameover = true; return; }
					entt::entity sl_ent = m_shiplives[m_shiplives.size() - 1];
					m_registry.erase<TransformComponent>(sl_ent);
					m_shiplives.pop_back();
					respawnTimer = std::clock();
					respawnInvincibility = true;
					std::cout << "SAT Collision Detected" << std::endl;
				}
			}
		}
	}
}
bool SATCollision::SeperatingAxisCollision(const std::vector<glm::vec2>& pol1, const std::vector<glm::vec2>& pol2, const glm::vec2& p1normal1, const glm::vec2& p1normal2, const glm::vec2& p1normal3, const glm::vec2& p1normal4) 
{

	const glm::vec2 p2edge1 = pol2[1] - pol2[0];
	const glm::vec2 p2edge2 = pol2[2] - pol2[1];
	const glm::vec2 p2edge3 = pol2[3] - pol2[2];
	const glm::vec2 p2edge4 = pol2[0] - pol2[3];
	const glm::vec2 p2normal1 = glm::vec2(p2edge1.y, -p2edge1.x);
	const glm::vec2 p2normal2 = glm::vec2(p2edge2.y, -p2edge2.x);
	const glm::vec2 p2normal3 = glm::vec2(p2edge3.y, -p2edge3.x);
	const glm::vec2 p2normal4 = glm::vec2(p2edge4.y, -p2edge4.x);

	std::pair<float, float>projvals1 = ProjVerts(pol1, p1normal1);
	std::pair<float, float>projvals2 = ProjVerts(pol2, p1normal1);
	if (projvals1.first >= projvals2.second || projvals2.first >= projvals1.second) {
		return false;
	}
	std::pair<float, float>projvals3 = ProjVerts(pol1, p1normal2);
	std::pair<float, float>projvals4 = ProjVerts(pol2, p1normal2);
	if (projvals3.first >= projvals4.second || projvals4.first >= projvals3.second) {
		return false;
	}
	std::pair<float, float>projvals5 = ProjVerts(pol1, p1normal3);
	std::pair<float, float>projvals6 = ProjVerts(pol2, p1normal3);
	if (projvals5.first >= projvals6.second || projvals6.first >= projvals5.second) {
		return false;
	}
	std::pair<float, float>projvals7 = ProjVerts(pol1, p1normal4);
	std::pair<float, float>projvals8 = ProjVerts(pol2, p1normal4);
	if (projvals7.first >= projvals8.second || projvals8.first >= projvals7.second) {
		return false;
	}


	std::pair<float, float>projvals9 = ProjVerts(pol1, p2normal1);
	std::pair<float, float>projvals10 = ProjVerts(pol2, p2normal1);
	if (projvals9.first >= projvals10.second || projvals10.first >= projvals9.second) {
		return false;
	}
	std::pair<float, float>projvals11 = ProjVerts(pol1, p2normal2);
	std::pair<float, float>projvals12 = ProjVerts(pol2, p2normal2);
	if (projvals11.first >= projvals12.second || projvals12.first >= projvals11.second) {
		return false;
	}
	std::pair<float, float>projvals13 = ProjVerts(pol1, p2normal3);
	std::pair<float, float>projvals14 = ProjVerts(pol2, p2normal3);
	if (projvals13.first >= projvals14.second || projvals14.first >= projvals13.second) {
		return false;
	}
	std::pair<float, float>projvals15 = ProjVerts(pol1, p2normal4);
	std::pair<float, float>projvals16 = ProjVerts(pol2, p2normal4);
	if (projvals15.first >= projvals16.second || projvals16.first >= projvals15.second) {
		return false;
	}

	return true;


}
std::pair<float, float> SATCollision::ProjVerts(const std::vector<glm::vec2>& v1, const glm::vec2& axis)
{
	float minA = std::numeric_limits<float>::max();
	float maxA = std::numeric_limits<float>::min();
	for (int i = 0; i < v1.size(); i++) {
		float proj = glm::dot(v1[i], axis);
		if (proj > maxA) { maxA = proj; }
		if (proj < minA) { minA = proj; }
	}
	std::pair<float, float> projvals{ minA, maxA };
	return projvals;
}
