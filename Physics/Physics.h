#pragma once
#include <algorithm>
#include <vector>
#include <glm-0.9.9.8/glm/glm.hpp>

std::pair<float, float> ProjVerts(const std::vector<glm::vec2>& v1, const glm::vec2& axis);

bool SeperatingAxisCollision(const std::vector<glm::vec2>& pol1, const std::vector<glm::vec2>& pol2, const glm::vec2& p1normal1, const glm::vec2& p1normal2, const glm::vec2& p1normal3, const glm::vec2& p1normal4);