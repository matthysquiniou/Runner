#include "pch.h"
#include "Physics.h"
#include "Entity.h"

void Physics::Update(Entity* entity, float deltaTime) {

		entity->m_velocity += m_gravity * deltaTime * entity->getWeight();

    if (std::abs(entity->m_velocity.x) > m_maxVelocity)
        entity->m_velocity.x = (entity->m_velocity.x > 0 ? m_maxVelocity : -m_maxVelocity);

    if (std::abs(entity->m_velocity.y) > m_maxVelocity)
        entity->m_velocity.y = (entity->m_velocity.y > 0 ? m_maxVelocity : -m_maxVelocity);

    if (std::abs(entity->m_velocity.z) > m_maxVelocity)
        entity->m_velocity.z = (entity->m_velocity.z > 0 ? m_maxVelocity : -m_maxVelocity);
}