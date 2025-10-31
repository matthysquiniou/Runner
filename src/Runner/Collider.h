#pragma once
#include "EntityTag.h"
#include "BoxTag.h"
#include "GCSR.h"

class Box;
class EntityManager;
class Collider {
public:
	Collider(EntityManager* em);
	void Collide();

private:
	bool ShouldCollide(EntityTag entityTag1, EntityTag entityTag2) const;
	bool ShouldCollide(BoxTag boxTag1, BoxTag boxTag2) const;

	gce::Vector3f32 CheckCollision(Box* box1, Box* box2) const;

private:
	EntityManager* m_em;
	gce::Vector3f32 m_zeroPenetration;
};