#include "MoveSystem.h"

void MoveSystem::update(entt::registry& m_registry, float dt)
{
	auto astupdate = m_registry.view<AsteroidComponent>();
	for (auto& entity: astupdate)
	{
		auto getStatus = astupdate.get<AsteroidComponent>(entity);
		if (getStatus.astimpact)
		{
			m_registry.erase<TransformComponent>(entity);
			m_registry.erase<RigidBodyComponent>(entity);
			m_registry.erase<AsteroidComponent>(entity);
		}
	}
	auto bulletupdate = m_registry.view<TransformComponent, BulletComponent>();
	for (auto& entity : bulletupdate)
	{
		const auto& getPos = bulletupdate.get<TransformComponent>(entity);
		auto& getStatus = bulletupdate.get<BulletComponent>(entity);
		std::cout << getStatus.m_bulletoriginalpos.x << " " << getStatus.m_bulletoriginalpos.x << std::endl;
		if (std::fabs(getStatus.m_bulletoriginalpos.x - getPos.m_pos.x) >= 600.0f || std::fabs(getStatus.m_bulletoriginalpos.y - getPos.m_pos.y) >= 600.0f)
		{
			std::cout << "deletion time" << std::endl;
			getStatus.impact = true;
		}
		if (getStatus.impact)
		{
			m_registry.erase<TransformComponent>(entity);
			m_registry.erase<RigidBodyComponent>(entity);
			m_registry.erase<BulletComponent>(entity);
		}
	}

	auto view = m_registry.view<TransformComponent, RigidBodyComponent>(entt::exclude<PlayerComponent>);
	view.each([&](auto& spr, auto& vel)
		{
			spr.m_pos.y += vel.m_velocity.x * dt * cos(spr.m_angle);
			spr.m_pos.x += vel.m_velocity.y * dt * -sin(spr.m_angle);

			if (spr.m_pos.x + (spr.m_size.x / 2) <= -805.0f || spr.m_pos.x - (spr.m_size.x / 2) >= 805.0f) {
				spr.m_pos.x *= -0.9f;
			}
			if (spr.m_pos.y + (spr.m_size.y / 2) <= -605.0f || spr.m_pos.y - (spr.m_size.y / 2) >= 605.0f) {
				spr.m_pos.y *= -0.9f;
			}
		});
	auto playerview = m_registry.view<TransformComponent, RigidBodyComponent, PlayerComponent>(entt::exclude<AsteroidComponent>);
	playerview.each([&](auto& spr, auto& vel, auto pl)
		{
			/*spr.m_pos.y += vel.m_velocity * dt * cos(spr.m_angle);
			spr.m_pos.x += vel.m_velocity * dt * -sin(spr.m_angle);*/

			if (spr.m_pos.x + (spr.m_size.x / 2) <= -805.0f || spr.m_pos.x - (spr.m_size.x / 2) >= 805.0f) {
				spr.m_pos.x *= -0.9f;
			}
			if (spr.m_pos.y + (spr.m_size.y / 2) <= -605.0f || spr.m_pos.y - (spr.m_size.y / 2) >= 605.0f) {
				spr.m_pos.y *= -0.9f;
			}
		});


}