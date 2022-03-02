#include "Physics.h"

std::pair<float, float> ProjVerts(const std::vector<glm::vec2>& v1, const glm::vec2& axis)
{
	float minA = FLT_MAX;
	float maxA = FLT_MIN;
	for (int i = 0; i < v1.size(); i++) {
		float proj = glm::dot(v1[i], axis);
		if (proj > maxA) { maxA = proj; }
		if (proj < minA) { minA = proj; }
	}
	std::pair<float, float> projvals{ minA, maxA };
	return projvals;

}

bool SeperatingAxisCollision(const std::vector<glm::vec2>& pol1, const std::vector<glm::vec2>& pol2, const glm::vec2& p1normal1, const glm::vec2& p1normal2, const glm::vec2& p1normal3, const glm::vec2& p1normal4)
{
	glm::vec2 p2edge1 = pol2[1] - pol2[0];
	glm::vec2 p2edge2 = pol2[2] - pol2[1];
	glm::vec2 p2edge3 = pol2[3] - pol2[2];
	glm::vec2 p2edge4 = pol2[0] - pol2[3];
	glm::vec2 p2normal1 = glm::vec2(p2edge1.y, -p2edge1.x);
	glm::vec2 p2normal2 = glm::vec2(p2edge2.y, -p2edge2.x);
	glm::vec2 p2normal3 = glm::vec2(p2edge3.y, -p2edge3.x);
	glm::vec2 p2normal4 = glm::vec2(p2edge4.y, -p2edge4.x);

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