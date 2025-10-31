#include "Camera.h"
#include "Entity.h"
#include "GameManager.h"
#include "Character.h"
#include <cmath>
#include <algorithm>

Camera::Camera(gce::Vector3f32 position, gce::Vector3f32 rotation, float fov, float farPlane, float nearPlane, gce::Vector3f32 offSet)
    : m_position(position)
    , m_rotation(rotation)
    , m_fov(fov)
    , m_farPlane(farPlane)
    , m_nearPlane(nearPlane)
    , m_offSet(offSet)
    , m_initialPosition(position)
    , m_initialRotation(rotation)
    , m_initialOffSet(offSet)
    , m_targetEntity(nullptr)
    , win(GameManager::GetInstance()->GetWindow())

{
    m_camera = new sr::Camera(sr::CameraType::PERSPECTIVE);
    m_camera->SetPosition(position + offSet);
    m_camera->SetRotation(rotation);
    m_camera->SetFOV(fov);
    m_camera->SetFarPlane(farPlane);
    m_camera->SetNearPlane(nearPlane);

    m_limitX = static_cast<float>(gce::PI) / 12.0f;
    m_limitY = static_cast<float>(gce::PI) / 12.0f;

    width = win.GetWidth();
    height = win.GetHeight();
}


sr::Camera& Camera::GetCamera() {
    return *m_camera;
}

gce::Vector3f32 Camera::MouseDirectionFromMiddle(gce::Vector2i32 current) const
{
	GameManager* gameManager = GameManager::GetInstance();
	float winHeight = static_cast<float>(gameManager->GetWindow().GetHeight());
	float winWidth = static_cast<float>(gameManager->GetWindow().GetWidth());

    float dx = static_cast<float>(current.x - (winWidth * 0.5));
    float dy = static_cast<float>((winHeight * 0.5) - current.y);

    gce::Vector3f32 dir = { dx, dy, 0.0f };
    return dir.Normalize();
}

void Camera::RotateAround(gce::Vector3f32 center, gce::Vector3f32 rotation)
{
    gce::Vector3f32 relativePosition = m_camera->GetPosition() - center;

    if (rotation.x != 0.f)
    {
        float cosX = std::cos(rotation.x);
        float sinX = std::sin(rotation.x);
        float newY = relativePosition.y * cosX - relativePosition.z * sinX;
        float newZ = relativePosition.y * sinX + relativePosition.z * cosX;
        relativePosition.y = newY;
        relativePosition.z = newZ;
    }

    if (rotation.y != 0.f)
    {
        float cosY = std::cos(rotation.y);
        float sinY = std::sin(rotation.y);
        float newX = relativePosition.x * cosY - relativePosition.z * sinY;
        float newZ = relativePosition.x * sinY + relativePosition.z * cosY;
        relativePosition.x = newX;
        relativePosition.z = newZ;
    }

    if (rotation.z != 0.f)
    {
        float cosZ = std::cos(rotation.z);
        float sinZ = std::sin(rotation.z);
        float newX = relativePosition.x * cosZ - relativePosition.y * sinZ;
        float newY = relativePosition.x * sinZ + relativePosition.y * cosZ;
        relativePosition.x = newX;
        relativePosition.y = newY;
    }

    m_offSet = relativePosition;
    SetPositionWithOffSet(center);

    m_camera->Rotate(-rotation);

    m_rotation.x += rotation.x;
    m_rotation.y += rotation.y;
    m_rotation.z += rotation.z;
}

float Camera::ClampPitch(float& yaw, gce::Vector3f32 dir, float deltaTime, float limit)
{
    float pitchDelta = dir.x * m_mouseSensitivity * deltaTime;
    float proposedPitch = m_pitch + pitchDelta;
    float clampedPitch = std::clamp(proposedPitch, -limit, limit);
    m_actualPitchDelta = clampedPitch - m_pitch;
    m_pitch = clampedPitch;

    return m_actualPitchDelta;
}

float Camera::ClampYaw(float& yaw, gce::Vector3f32 dir, float deltaTime, float limit)
{
    float yawDelta = dir.y * m_mouseSensitivity * deltaTime;
    float proposedYaw = m_yaw + yawDelta;
    float clampedYaw = std::clamp(proposedYaw, -limit, limit);
    m_actualYawDelta = clampedYaw - m_yaw;
    m_yaw = clampedYaw;

    return m_actualYawDelta;
}

void Camera::MoveCameraToCursor(float deltaTime, Entity* entity)
{
    Character* character = dynamic_cast<Character*>(entity);

    m_targetCharacter = character;

    m_mousePos = sr::GetMousePosition();

    SetOffSet(m_setOffCameraFirstPerson);

    gce::Vector3f32 center = m_targetCharacter->getPosition();
    SetPositionWithOffSet(center);

    m_nx = (static_cast<float>(m_mousePos.x) - (width * 0.5f)) / static_cast<float>(width);
    m_ny = ((height * 0.5f) - static_cast<float>(m_mousePos.y)) / static_cast<float>(height);

    m_yawDelta = m_nx * m_mouseSensitivity * deltaTime;
    m_pitchDelta = m_ny * m_mouseSensitivity * deltaTime;

    m_tmpDir = { m_nx, m_ny, 0.0f };

    m_appliedPitch = ClampPitch(m_pitch, m_tmpDir, deltaTime, m_limitX);
    m_appliedYaw = ClampYaw(m_yaw, m_tmpDir, deltaTime, m_limitY);

    if (std::abs(m_appliedYaw) > std::abs(m_appliedPitch))
        RotateAround(center, { m_appliedYaw, 0.0f, 0.0f });
    else if (std::abs(m_appliedPitch) > 0.0f)
        RotateAround(center, { 0.0f, -m_appliedPitch, 0.0f });
}
void Camera::SetPositionWithOffSet(gce::Vector3f32 position) {
    m_camera->SetPosition(position + m_offSet);
}

void Camera::Reset()
{
    m_position = m_initialPosition;
    m_rotation = m_initialRotation;
    m_offSet = m_initialOffSet;

    if (m_camera) {
        m_camera->SetPosition(m_position + m_offSet);
        m_camera->SetRotation(m_rotation);
    }
}

