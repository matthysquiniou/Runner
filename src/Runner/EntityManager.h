#pragma once
#include "Entity.h"
#include "EntityTag.h"

class Collider;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	void AddEntityBuffer(Entity* entity);
	void Add();

	void RemoveDeadEntities();
	std::vector<Entity*> GetEntitiesOfTag(const EntityTag entityTag);
	std::vector<Entity*>& GetAllEntities();
	void Collide();

private:
	std::vector<Entity*> m_entities;
	std::vector<Entity*> m_entitiesBuffer;
	Collider* m_collider;
};

