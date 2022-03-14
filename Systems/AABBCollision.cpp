#include "AABBCollision.h"

void AABBCollision::update(entt::registry& m_registry, float dt)
{	
	auto bulletview = m_registry.view<TransformComponent, BulletComponent>();
	for (auto& entity: bulletview)
	{
		auto& bulpos = bulletview.get<TransformComponent>(entity);
		auto astview = m_registry.view<TransformComponent, RigidBodyComponent, AsteroidComponent>();
		for (auto& astentity: astview)
		{
			auto& astcheck = astview.get<TransformComponent>(astentity);
			auto& astStatus = astview.get<AsteroidComponent>(astentity);
			if (astcheck.m_pos.x - (astcheck.m_size.x / 2) < bulpos.m_pos.x + (bulpos.m_size.x / 2) &&
				astcheck.m_pos.x + (astcheck.m_size.x / 2) > bulpos.m_pos.x - (bulpos.m_size.x / 2) &&
				astcheck.m_pos.y - (astcheck.m_size.y / 2) < bulpos.m_pos.y + (bulpos.m_size.y / 2) &&
				astcheck.m_pos.y + (astcheck.m_size.y / 2) > bulpos.m_pos.y - (bulpos.m_size.y / 2))
			{				
				if (astcheck.m_size.x > 50.0f)
				{					
					std::cout << "Collision" << std::endl;
					const auto newAst = m_registry.create();
					const auto newAst1 = m_registry.create();
					m_registry.emplace<TransformComponent>(newAst, astcheck.m_pos, astcheck.m_size / 2.0f, rand() % 100 + 100, "asteroids");
					m_registry.emplace<RigidBodyComponent>(newAst, glm::vec3(rand() % 10 + 200, rand() % 10 + 200, 0.0f));
					m_registry.emplace<AsteroidComponent>(newAst);
					m_registry.emplace<TransformComponent>(newAst1, astcheck.m_pos, astcheck.m_size / 2.0f, rand() % 100 + 100, "asteroids");
					m_registry.emplace<RigidBodyComponent>(newAst1, glm::vec3(rand() % 10 + 200, rand() % 10 + 200, 0.0f));
					m_registry.emplace<AsteroidComponent>(newAst1);
					std::cout << "pre" << std::endl;
					std::cout << "post" << std::endl;					
				}
				astStatus.astimpact = true;
				auto& bulletStatus = bulletview.get<BulletComponent>(entity);
				bulletStatus.impact = true;
				std::cout << "collision function ends" << std::endl;
				std::cout << astview.size_hint() << std::endl;
			}
		}
	}
}