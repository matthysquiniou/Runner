#pragma once
#include "Entity.h"

class Character;
class EntityManager;

class Shoot : public Entity
{
public:
	Shoot(EntityManager* entityManager, Character* character, gce::Vector3f32 direction, gce::Vector3f32 offset = { 0.0f, 3.5f, 5.0f }, gce::Vector3f32 color = {0.0f, 0.0f, 0.0f});

	void Update(float deltaTime) override;

	void Collide(gce::Vector3f32 penetration, BoxTag ownBoxTag, Entity* targetEntity, BoxTag targetBoxTag) override;

	EntityTag GetTag() const override;

private:

	Character* m_character;
	EntityManager* m_entityManager;

	float m_speed = 50.f;
	float m_lifeTime = 5.f;
	float m_currentLife = 0.f;

	gce::Vector3f32 m_offset;
	gce::Vector3f32 m_scale;
	gce::Vector3f32 m_spawnPos;
	gce::Vector3f32 m_direction;
	gce::Vector3f32 m_color;

};

