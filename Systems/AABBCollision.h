#pragma once
#include<entt/entt.hpp>
#include "../Components/Components.h"
#include <iostream>
class AABBCollision
{
public:
	AABBCollision() = default;
	~AABBCollision() = default;

	void update(entt::registry& m_registry, float dt);

};