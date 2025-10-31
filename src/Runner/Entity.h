#pragma once
#include "EntityTag.h"
#include "BoxTag.h"
#include <GCSR.h>

class Mesh;
class Box;
class EntityManager;

class Entity {

public:
	Entity(Mesh* mesh);
	~Entity();

	virtual void Update(float deltaTime) = 0;
	void Render();

	virtual void Collide(gce::Vector3f32 penetration, BoxTag ownBoxTag, Entity* targetEntity, BoxTag targetBoxTag);
	virtual EntityTag GetTag() const;

	bool IsDead() const;

	virtual void Translate(gce::Vector3f32 translation);
	virtual void Rotate(gce::Vector3f32 rotation);

	gce::Vector3f32 getPosition();
	std::vector<Box*>& getBoxs();
	float getWeight() const;

	void SetEntityManager(EntityManager* manager) { m_entityManager = manager; }

public:
	gce::Vector3f32 m_velocity = { 0.f, 0.f, 0.f };
	bool m_dead = false;

protected:
	float m_weight = 1.f;
	std::vector<Box*> m_boxes;
	Mesh* m_mesh;
	EntityManager* m_entityManager = nullptr;
};