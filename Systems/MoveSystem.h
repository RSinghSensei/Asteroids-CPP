#pragma once
#include <entt/entt.hpp>
#include "../Components/Components.h"
class MoveSystem
{
public:
	MoveSystem() = default;
	~MoveSystem() = default;
	void update(entt::registry& m_registry, float dt);
};
