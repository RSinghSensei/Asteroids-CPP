#include "respawnSystem.h"

void respawnSystem::update(entt::registry& m_registry, float dt, std::clock_t& respawnTimer, bool& respawnInvincibility)
{
	if (respawnInvincibility)
	{
		auto view = m_registry.view<TransformComponent, PlayerComponent>();
		for (auto& entity : view)
		{
			auto& p1 = view.get<TransformComponent>(entity);
			if (((std::clock() - respawnTimer) / ((double)CLOCKS_PER_SEC)) >= 0.0 && ((std::clock() - respawnTimer) / ((double)CLOCKS_PER_SEC)) < 0.5) { p1.m_pos.z = -2.0f; }
			else if (((std::clock() - respawnTimer) / ((double)CLOCKS_PER_SEC)) >= 0.5 && ((std::clock() - respawnTimer) / ((double)CLOCKS_PER_SEC)) < 1.0) { p1.m_pos.z = 1.0f; }
			else if (((std::clock() - respawnTimer) / ((double)CLOCKS_PER_SEC)) >= 1.0 && ((std::clock() - respawnTimer) / ((double)CLOCKS_PER_SEC)) < 1.5) { p1.m_pos.z = -2.0f; }
			else if (((std::clock() - respawnTimer) / ((double)CLOCKS_PER_SEC)) >= 1.5 && ((std::clock() - respawnTimer) / ((double)CLOCKS_PER_SEC)) < 2.0) { p1.m_pos.z = 1.0f; }
			else if (((std::clock() - respawnTimer) / ((double)CLOCKS_PER_SEC)) >= 2.0 && ((std::clock() - respawnTimer) / ((double)CLOCKS_PER_SEC)) < 2.4) { p1.m_pos.z = -2.0f; }
			else if (((std::clock() - respawnTimer) / ((double)CLOCKS_PER_SEC)) >= 2.5) { respawnInvincibility = false; p1.m_pos.z = 1.0f; }
		}
	}
}