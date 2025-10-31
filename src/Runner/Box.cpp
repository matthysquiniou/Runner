#include "Box.h"

Box::Box(BoxTag boxTag, gce::Vector3f32 position, gce::Vector3f32 scale) : 
	m_boxTag(boxTag),
	m_position(position),
	m_scale(scale)
{}

BoxTag Box::GetTag() const {
	return m_boxTag;
}

gce::Vector3f32 Box::GetPosition() const {
	return m_position;
}

gce::Vector3f32 Box::GetScale() const {
	return m_scale;
}

void Box::Translate(gce::Vector3f32 translation) {
	m_position += translation;
}