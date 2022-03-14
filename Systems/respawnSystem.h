#pragma once
#include <entt/entt.hpp>
#include <ctime>
#include "../Components/Components.h"

class respawnSystem
{
public:
	respawnSystem() = default;
	~respawnSystem() = default;
	void update(entt::registry& m_registry, float dt, std::clock_t& respawnTimer, bool& respawnInvincibility);
};

