#pragma once

#include "Entity.h"
#include "ObstacleTag.h"

class EntityManager;
class SceneGamePlay;
class Charcter;

class Obstacle : public Entity
{
public:
	Obstacle(gce::Vector3f32 position, gce::Vector3f32 scale, ObstacleTag tag = ObstacleTag::SIZEOBSTACLE);

	void GenerateRandomObstacle();
	void GenerateObstacle();
	void Collide(gce::Vector3f32 penetration, BoxTag ownBoxTag, Entity* targetEntity, BoxTag targetBoxTag) override;
	void ObstacleAnimation(float deltaTime);

	void AddBoxObstacle(gce::Vector3f32 scale, gce::Vector3f32 position, bool hasCollision = false, bool hasHitBox = false);

	void Update(float deltaTime) override;

	ObstacleTag GetObstacleTag() const { return m_obstacleTag; }

	EntityTag GetTag() const override;
	Mesh* InitMesh();


private:
	void GenerateRandomVelocity();
	void GenerateRandomPos(float x, float y);

private:

	EntityManager* m_entityManager = nullptr;
	Entity* m_character = nullptr;
	// animation

	float m_initialYPosition = 0.0f;

	gce::Vector3f32 m_velocity = { 0.f,0.f,0.f };
	gce::Vector3f32 m_rotation = { 0.f,0.f,0.f };
	gce::Vector3f32 m_randomPos = { 1.f,10.f,0.f };

	static std::vector<std::shared_ptr<sr::Texture>> m_obstacleTextures;
	bool m_laserActivationFlag = false;
	gce::Vector3f32 m_tilePosition;
	gce::Vector3f32 m_tileScale;

	ObstacleTag m_obstacleTag = ObstacleTag::SIZEOBSTACLE;

	SceneGamePlay* m_sceneGamePlay = nullptr;

};
