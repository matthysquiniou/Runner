#include "pch.h"
#include "Mesh.h"
#include "GameManager.h"

Mesh::~Mesh()
{
	for (size_t i = 0; i < m_geometries.size(); i++)
	{
		sr::Geometry* geometry = m_geometries[i];
		geometry->SetRotation({ 0.f,0.f,0.f });
		geometry->SetColor({ 0.f,0.f,0.f });
		GameManager::GetGeometryPool().Release(geometry);
		GameManager::GetOrcPool().Release(geometry);
	}
}

void Mesh::Render(sr::Window* window) {
	for (size_t i = 0; i < m_geometries.size(); i++)
	{
		sr::Geometry* geometry = m_geometries[i];
		window->Draw(*geometry);
	}
}

void Mesh::Translate(gce::Vector3f32 translation) {
	for (size_t i = 0; i < m_geometries.size(); i++)
	{
		sr::Geometry* geometry = m_geometries[i];
		geometry->Translate(translation);
	}
}

void Mesh::Rotate(gce::Vector3f32 rotation) {
	
	CalculateCenter();
	
	for (size_t i = 0; i < m_geometries.size(); i++)
	{
		sr::Geometry* geometry = m_geometries[i];
		RotateAroundCenter(geometry, rotation);
	}
}

void Mesh::AddGeometry(sr::Geometry* geometry) {
	m_geometries.push_back(geometry);
	m_center_calculated = false;
}

gce::Vector3f32 Mesh::GetCenter() {
	CalculateCenter();
	return m_center;
}

void Mesh::CalculateCenter() {
	gce::Vector3f32 totalPos = { 0.f, 0.f, 0.f };
	for (size_t i = 0; i < m_geometries.size(); i++)
	{
		sr::Geometry* geometry = m_geometries[i];
		totalPos += geometry->GetPosition();
	}
	m_center = totalPos / static_cast<float>(m_geometries.size());
}

void Mesh::RotateAroundCenter(sr::Geometry* geometry, gce::Vector3f32 rotation) {
	gce::Vector3f32 relativePostion = geometry->GetPosition() - m_center;

	if (rotation.x != 0.f)
	{
		float cosX = std::cos(rotation.x);
		float sinX = std::sin(rotation.x);
		float newY = relativePostion.y * cosX - relativePostion.z * sinX;
		float newZ = relativePostion.y * sinX - relativePostion.z * cosX;
		relativePostion.y = newY;
		relativePostion.z = newZ;
	}

	if (rotation.y != 0.f)
	{
		float cosY = std::cos(rotation.y);
		float sinY = std::sin(rotation.y);
		float newX = relativePostion.x * cosY - relativePostion.z * sinY;
		float newZ = relativePostion.x * sinY - relativePostion.z * cosY;
		relativePostion.x = newX;
		relativePostion.z = newZ;
	}

	if (rotation.z != 0.f)
	{
		float cosZ = std::cos(rotation.z);
		float sinZ = std::sin(rotation.z);
		float newX = relativePostion.x * cosZ - relativePostion.y * sinZ;
		float newY = relativePostion.x * sinZ - relativePostion.y * cosZ;
		relativePostion.x = newX;
		relativePostion.y = newY;
	}

	geometry->SetPosition(m_center + relativePostion);
	geometry->Rotate(rotation);
}

