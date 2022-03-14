#include "GameOver.h"

void GameOver::update(entt::registry& m_registry, float dt, bool &isOver, bool &gameactive)
{
	if (isOver) { gameoverswitch = true; }
	if (gameoverswitch)
	{
		/*auto view = m_registry.view<TransformComponent, PlayerComponent>();
		for (auto& entity : view)
		{
			auto& p1 = view.get<TransformComponent>(entity);
		}*/
		const auto gameoverImage = m_registry.create();
		m_registry.emplace<TransformComponent>(gameoverImage, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1600.0f, 1200.0f, 1.0f), 0.0f, "gameover");
		isOver = false;
		gameoverswitch = false;
		gameactive = true;
	}
}