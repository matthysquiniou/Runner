#pragma once
#include "Entity.h"
#include "SceneManager.h"
#include "Camera.h"

class EntityManager;
class Physics;
class GameManager;
class Shoot;
class PowerUp;
class Controller;

class Character : public Entity
{
public:
    Character(Mesh* mesh, float speed, EntityManager* entityManager, Camera* camera);

    void Collide(gce::Vector3f32 penetration, BoxTag ownBoxTag, Entity* targetEntity, BoxTag targetBoxTag) override;

    void Update(float deltaTime) override;

    EntityTag GetTag() const override;

    void Translate(gce::Vector3f32 offset) override;
    void RotatePlayer(gce::Vector3f32 rotation);

	void AddAcceleration(float value) { m_acceleration += value; }
	void SetAcceleration(float velocity) { m_acceleration = velocity; }
    int GetAcceleration() const { return m_acceleration; }
	float GetMaxAcceleration() const { return m_maxAcceleration + m_speed; }
	float GetVelocity() const { return m_velocity.z; }

	float GetJetPackFuel() const { return m_JetPackFuel; }
	float GetMaxJetPackFuel() const { return m_MaxJetPackFuel; }
	void SetJetPackFuel(float value) { m_JetPackFuel = value; }

	bool GetIsGrounded() const { return m_isGrounded; }

    void SetPowerUpActive(bool active) { m_powerIsCurentlyAtive = active; }
	bool GetPowerUpIsActive() const { return m_powerIsCurentlyAtive; }

    void SetActivePowerUpTimer(float t) { m_activePowerUpTimer = t; }
    float GetActivePowerUpTimer() const { return m_activePowerUpTimer; }

	void SetJumpHeightBoost(float height) { m_jumpHeightBoost = height; }
	void SetJumpBoostIsActive(bool active) { m_jumpBoostActive = active; }
	bool GetJumpBoostIsActive() const { return m_jumpBoostActive; }

	bool GetSpeedBoostIsActive() const { return m_speedBoostActive; }
	void SetSpeedBoostIsActive(bool active) { m_speedBoostActive = active; }

	bool GetFlyingBoostIsActive() const { return m_flyingBoostActive; }
	void SetFlyingBoostIsActive(bool active) { m_flyingBoostActive = active; }

	bool GetScoreBoostIsActive() const { return scoreBoostActive; }
    int GetPowerUpScoreMultiplier() const { return m_powerUpScoreMultiplier; }
    void SetPowerUpScoreMultiplier(int v) { m_powerUpScoreMultiplier = v; }
	void SetScoreBoostIsActive(bool active) { scoreBoostActive = active; }

    void DeathSequence(float deltaTime);

    void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void Jump();
	void JetPackUp(float deltaTime);
	void JetPackDown(float deltaTime);
	void ShootForward();
	void LookAhead(float deltaTime);

    friend class Controller;

private:

	//class pointers
    GameManager* m_gameManager;
    SceneManager* m_sceneManager;
    EntityManager* m_entityManager;
    Camera* m_camera;
    Physics* m_physics;
    Mesh* m_mesh;
    Shoot* m_shoot;
	PowerUp* m_powerUp;

    sr::Light* m_light;
    sr::Custom* m_player;

	//texture
	std::shared_ptr<sr::Texture> m_texture;

	//position and scale
    gce::Vector3f32 m_position;
    gce::Vector3f32 m_scale;

	//JetPack
	float m_velocityJetPack = 75.0f;
	float m_JetPackFuel;
    float m_JetPackFuelRecharge = 1.f;
	float m_MaxJetPackFuel = 100.0f;

    //movement
	float m_acceleration;
	float m_maxAcceleration = 30.0f;
    float m_speed;
    float m_jumpHeight = 20.f;
	float m_jumpHeightBoost = 0.f;

    gce::Vector3f32 m_PlayerRotation;

    gce::Vector3f32 m_rotation;

	//timers
    float m_timeAccumulator;
    float m_activePowerUpTimer = 0.0f;

	//boolean
    bool m_isGrounded = false;
    bool m_isAlive = true;

	//shooting
    gce::Vector3f32 m_directionShoot;

    const gce::Vector3f32 m_backOffSet = { 0.0f, 5.0f, -1.0f };
    const gce::Vector3f32 m_SpaceBetwinTrailOffSet = { 2.0f, 0.0f, 0.0f };

    float m_reloadTime = 0.5f;
	float m_currentReload = 0.0f;

    //color
	const gce::Vector3f32 m_white = { 1.0f, 1.0f, 1.0f };
    const gce::Vector3f32 m_orange = { 1.0f, 0.5f, 0.0f };
	const gce::Vector3f32 m_red = { 1.0f, 0.0f, 0.0f };

	gce::Vector3f32 m_currentColor;



    //powerup
	bool m_powerIsCurentlyAtive = false;
	bool m_speedBoostActive = false;
	bool m_jumpBoostActive = false;
	bool m_flyingBoostActive = false;
	bool scoreBoostActive = false;

    int m_powerUpScoreMultiplier = 4;
};
