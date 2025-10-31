#pragma once
#include "BoxTag.h"
#include "GCSR.h"

class Box {
public:
	Box(BoxTag boxtype, gce::Vector3f32 position, gce::Vector3f32 scale);
	BoxTag GetTag() const;
	gce::Vector3f32 GetPosition() const;
	gce::Vector3f32 GetScale() const;
	void Translate(gce::Vector3f32 translation);
private:
	BoxTag m_boxTag;
	gce::Vector3f32 m_position;
	gce::Vector3f32 m_scale;
};