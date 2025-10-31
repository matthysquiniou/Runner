#pragma once

#include "GCSR.h"
#include "Mesh.h"

class Entity;
class Character;

class Camera
{
public:
	Camera(gce::Vector3f32 position, gce::Vector3f32 rotation, float fov, float farPlane, float nearPlane, gce::Vector3f32 offSet);
	~Camera() = default;

	void Reset();
	void RotateAround(gce::Vector3f32 center, gce::Vector3f32 rotation);

	float ClampPitch(float& yaw, gce::Vector3f32 dir, float deltaTime, float limit);
	float ClampYaw(float& yaw, gce::Vector3f32 dir, float deltaTime, float limit);

	void MoveCameraToCursor(float deltaTime, Entity* entity);

	void SetPositionWithOffSet(gce::Vector3f32 position);
	sr::Camera& GetCamera();

	gce::Vector3f32 MouseDirectionFromMiddle(gce::Vector2i32 current) const;
	sr::Camera* m_camera;

	void SetOffSet(gce::Vector3f32 offSet) { m_offSet = offSet; }
private:

	Character* m_targetCharacter = nullptr;

	//window
	sr::Window& win;
	uint32_t width;
	uint32_t height;

	gce::Vector3f32 m_initialPosition;
	gce::Vector3f32 m_initialRotation;
	gce::Vector3f32 m_initialOffSet;

	gce::Vector3f32 m_offSet;

	gce::Vector3f32 m_position;
	gce::Vector3f32 m_rotation;

	Entity* m_targetEntity;

	float m_fov;
	float m_nearPlane;
	float m_farPlane;

	//mouse
	gce::Vector2i32 m_mousePos;
	gce::Vector3f32 m_dir;
	gce::Vector2i32 m_prevMousePos;

	const float m_mouseSensitivity = 2.0f;

	//camera movement
	const gce::Vector3f32 m_setOffCameraFirstPerson = { 1.5f, 3.5f, 0.0f };

	float m_limitX;
	float m_limitY;

	float m_nx, m_ny;
	float m_yawDelta, m_pitchDelta;

	gce::Vector3f32 m_tmpDir;

	float m_actualYawDelta;
	float m_actualPitchDelta;

	float m_appliedPitch, m_appliedYaw;

	float m_yaw = 0.0f;
	float m_pitch = 0.0f;

};

