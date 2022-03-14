#pragma once
#include <entt/entt.hpp>
#include "../Components/Components.h"
class GameOver
{
public:
	GameOver() = default;
	~GameOver() = default;
	void update(entt::registry& m_registry, float dt, bool &isOver, bool& gameactive);
	bool gameoverswitch = false;

};
