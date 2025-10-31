#pragma once
#include "GCSR.h"

class Mesh {
public:

	~Mesh();

	void Render(sr::Window* window);
	void Translate(gce::Vector3f32 translation);
	void Rotate(gce::Vector3f32 rotation);
	void AddGeometry(sr::Geometry* geometry);
	gce::Vector3f32 GetCenter();

private:

	void CalculateCenter();
	void RotateAroundCenter(sr::Geometry* geometry, gce::Vector3f32 rotation);

private:
	gce::Vector3f32 m_center = { 0.f, 0.f, 0.f };
	bool m_center_calculated = false;
	std::vector<sr::Geometry*> m_geometries;
};