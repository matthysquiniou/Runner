#include "Shoot.h"
#include "GameManager.h"
#include "Box.h"
#include "BoxTag.h"
#include "Character.h"
#include "EntityManager.h"
#include <iostream>

Shoot::Shoot(EntityManager* entityManager, Character* character, gce::Vector3f32 direction, gce::Vector3f32 offset, gce::Vector3f32 color)
	: Entity(new Mesh()), m_character(character), m_entityManager(entityManager), m_direction(direction), m_offset(offset), m_color(color)
{
	m_scale = { 0.2f, 0.2f, 0.2f };
	m_currentLife = m_lifeTime;

	if (m_character)
		m_spawnPos = m_character->getPosition() + m_offset;

	sr::Cube* cube = GameManager::GetGeometryPool().Acquire<sr::Cube>();
	cube->SetPosition(m_spawnPos);
	cube->SetScale(m_scale);
	cube->SetColor(m_color);

	Box* hurtBox = new Box(BoxTag::HURT, m_spawnPos, m_scale);
	
	if (m_mesh)
		m_mesh->AddGeometry(cube);

	if (entityManager)
		entityManager->AddEntityBuffer(this);

	m_boxes.push_back(hurtBox);
}

void Shoot::Update(float deltaTime)
{
	if (m_currentLife > 0.f) {
		m_currentLife -= deltaTime;
		if (m_currentLife <= 0.f) { m_dead = true; return; }
	}

	float velocity = m_speed;
	if (m_character)
		velocity += static_cast<float>(m_character->GetAcceleration());

	gce::Vector3f32 movement = m_direction * velocity * deltaTime;

	this->Translate(movement);

	for (auto box : m_boxes)
	{
		if (box)
			box->Translate(movement);
	}
}

EntityTag Shoot::GetTag() const
{
	return EntityTag::BULLET;
}

void Shoot::Collide(gce::Vector3f32 penetration, BoxTag ownBoxTag, Entity* targetEntity, BoxTag targetBoxTag) 
{
	if (targetEntity->GetTag() == EntityTag::OBSTACLE && targetBoxTag == BoxTag::HIT)
	{
		m_dead = true;
	}
}

