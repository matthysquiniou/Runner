#include "pch.h"
#include "EntityManager.h"
#include "Collider.h"
#include <algorithm>
#include <iostream>

EntityManager::EntityManager()
{
    m_collider = new Collider(this);
}

EntityManager::~EntityManager()
{
    for (Entity* e : m_entities) {
        if (e) {
            delete e;
        }
    }
    m_entities.clear();
}

void EntityManager::AddEntityBuffer(Entity* entity)
{
    entity->SetEntityManager(this);
    m_entitiesBuffer.push_back(entity);
}

void EntityManager::Add()
{
    for (Entity* e : m_entitiesBuffer) {
        m_entities.push_back(e);
	}
	m_entitiesBuffer.clear();
}

void EntityManager::RemoveDeadEntities() {
    for (auto it = m_entities.begin(); it != m_entities.end();) {
        Entity* e = *it;
        if (e && e->IsDead()) {
            delete e;
            it = m_entities.erase(it);
        } else {
            ++it;
        }
    }
}

std::vector<Entity*> EntityManager::GetEntitiesOfTag(const EntityTag entityTag) 
{
	std::vector<Entity*> out;

	out.reserve(m_entities.size());

	std::copy_if(m_entities.begin(), m_entities.end(), std::back_inserter(out),[entityTag](Entity* entity) 
		{
			return entity->GetTag() == entityTag; 
		});
	return out;
}

std::vector<Entity*>& EntityManager::GetAllEntities() 
{
	return m_entities;
}

void EntityManager::Collide() {
    m_collider->Collide();
}