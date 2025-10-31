#pragma once
#include "Entity.h"
#include "Mesh.h"
#include "EntityManager.h"
#include "PowerUpTag.h"

class Character;
class SceneGamePlay;

class PowerUp : public Entity 
{
public: 
	PowerUp(gce::Vector3f32 position, PowerUpTag powerTag = PowerUpTag::POWER_SIZE);

	Mesh* InitMesh();

	void GeneratePowerUpPaths();

	void AddBoxPowerUp(gce::Vector3f32 pos, int textureIndex = 0, gce::Vector3f32 scaling = {3.f, 3.f, 3.f}, BoxTag tag = BoxTag::COLLIDER);

	void Update(float deltaTime) override;
	void Collide(gce::Vector3f32 penetration, BoxTag ownBoxTag, Entity* targetEntity, BoxTag targetBoxTag) override;

	void GenerateRandomPowerUp();
	void GeneratePowerUp(int powerUpindex);

	void ResetTimer() { m_powerUpTimerLocal = m_powerUpDurationLocal; }
	void PowerUpAnimation(float deltaTime);

	int GetPowerUpScoreMultiplier() const { return m_scoreBoostValue; }

	void ActivePowerUpEffect(Entity* entity, PowerUpTag tag = POWERUPSPEEDBOOST);

	EntityTag GetTag() const;
	PowerUpTag GetPowerTag() const { return m_powerTag; }

private:
	//annimation 
	float m_rotationSpeed = 5.0f;
	float m_bounceHeight = 0.5f;
	float m_bounceSpeed = 2.0f;
	float m_initialYPosition = m_position.y;

	float m_elapsedTime;

	static std::vector<std::shared_ptr<sr::Texture>> m_powerUpTextures;
	std::vector<float> m_powerUpDurations;

	gce::Vector3f32 m_position;

	PowerUpTag m_powerTag = PowerUpTag::POWER_SIZE;

	Character* m_targetCharacter;
	SceneGamePlay* m_sceneGamePlay;

	bool m_consumed = false;
	//powerup effect boost values
	float m_accelerationMultiplier = 2.0f;
	float m_jumpHeightBoostValue = 20.0f;
	float m_flyingBoostValue = 500.0f;
	float m_scoreBoostValue = 4.0f;

	//powerup effect timer values
	float m_powerUpDurationLocal = 25.0f;
	float m_powerUpTimerLocal = 25.0f;
	int m_nbOfPowerUpLocal = 0;
};

