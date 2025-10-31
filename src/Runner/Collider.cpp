#include "pch.h"
#include "Collider.h"
#include "Box.h"
#include "EntityManager.h"
#include "Entity.h";

Collider::Collider(EntityManager* em) : m_em(em), m_zeroPenetration({0.f, 0.f, 0.f}) {}

bool Collider::ShouldCollide(EntityTag entityTag1, EntityTag entityTag2) const {
	if (entityTag1 > entityTag2) std::swap(entityTag1, entityTag2) ;
	return (entityTag1 == EntityTag::CHARACTER && entityTag2 == EntityTag::TILE)
		|| (entityTag1 == EntityTag::CHARACTER && entityTag2 == EntityTag::OBSTACLE)
		|| (entityTag1 == EntityTag::CHARACTER && entityTag2 == EntityTag::POWERUP)
		|| (entityTag1 == EntityTag::BULLET && entityTag2 == EntityTag::OBSTACLE)
		|| (entityTag1 == EntityTag::BULLET && entityTag2 == EntityTag::TILE)
		|| (entityTag1 == EntityTag::TILE && entityTag2 == EntityTag::OBSTACLE);
}

bool Collider::ShouldCollide(BoxTag boxTag1, BoxTag boxTag2) const {
	if (boxTag1 > boxTag2) std::swap(boxTag1, boxTag2);
	return (boxTag1 == BoxTag::COLLIDER && boxTag2 == BoxTag::COLLIDER) 
		|| (boxTag1 == BoxTag::HIT && boxTag2 == BoxTag::HURT) 
		|| (boxTag1 == BoxTag::COLLIDER && boxTag2 == BoxTag::OBSERVER);
}

void Collider::Collide() {
	// maybe do a spacial grid latter 
	auto& entities = m_em->GetAllEntities();
	for (size_t entityIndex1 = 0; entityIndex1 < entities.size(); ++entityIndex1) {
		Entity* entity1 = entities[entityIndex1];

		for (size_t entityIndex2 = entityIndex1 + 1; entityIndex2 < entities.size(); ++entityIndex2) {
			Entity* entity2 = entities[entityIndex2];

			if (!ShouldCollide(entity1->GetTag(), entity2->GetTag())) continue;

			std::vector<Box*>& boxes1 = entity1->getBoxs();
			std::vector<Box*>& boxes2 = entity2->getBoxs();

			for (size_t boxIndex1 = 0; boxIndex1 < boxes1.size(); ++boxIndex1) {
				Box* box1 = boxes1[boxIndex1];
				BoxTag boxTag1 = box1->GetTag();

				for (size_t boxIndex2 = 0; boxIndex2 < boxes2.size(); ++boxIndex2) {
					Box* box2 = boxes2[boxIndex2];
					BoxTag boxTag2 = box2->GetTag();

					if (!ShouldCollide(boxTag1, boxTag2)) continue;

					gce::Vector3f32 penetration = CheckCollision(box1, box2);
					if (penetration == m_zeroPenetration) continue;

					entity1->Collide(-penetration, boxTag1, entity2, boxTag2);
					entity2->Collide(penetration, boxTag2, entity1, boxTag1);
				}
			}
		}
	}
}

gce::Vector3f32 Collider::CheckCollision(Box* box1, Box* box2) const {
	const gce::Vector3f32 half1 = box1->GetScale() * 0.5f;
	const gce::Vector3f32 half2 = box2->GetScale() * 0.5f;
	const gce::Vector3f32 pos1 = box1->GetPosition();
	const gce::Vector3f32 pos2 = box2->GetPosition();

	gce::Vector3f32 penetration = { 0.f,0.f,0.f };

	float dx = pos2.x - pos1.x;
	float px = (half1.x + half2.x) - std::abs(dx);

	if (px <= 0.f) 
		return m_zeroPenetration;

	penetration.x = (dx < 0.f) ? -px : px;

	float dy = pos2.y - pos1.y;
	float py = (half1.y + half2.y) - std::abs(dy);

	if (py <= 0.f) 
		return m_zeroPenetration;

	penetration.y = (dy < 0.f) ? -py : py;

	float dz = pos2.z - pos1.z;
	float pz = (half1.z + half2.z) - std::abs(dz);

	if (pz <= 0.f) 
		return m_zeroPenetration;

	penetration.z = (dz < 0.f) ? -pz : pz;

	return penetration;
}