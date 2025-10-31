#pragma once
#include "Entity.h"
#include "TileTag.h"

class PowerUp;
class Obstacle;
class EntityManager;
class SceneGamePlay;

class Tile:public Entity
{
public:

	Tile(TileTag tt, gce::Vector3f32 pos, float width, float lenght, float depth, float height, float lastYPos, bool isFirstTile = false);

	void AddTextureTilt(std::string path);
	std::string GetTexturePath(int index) const { return m_texture[index]; }

	void Update(float deltaTime) override;
	EntityTag GetTag() const override;

	void RegisterChildrenWithManager(EntityManager* em);

	friend class SceneGamePlay;
private:

	Mesh* InitMesh();
	void GenerateTexturePaths();

	void CreateTiles(TileTag tt, gce::Vector3f32 pos, float width, float lenght, float depth, float height, float lastYPos, bool isFirstTile);
	void CreateCeillingAndWall(gce::Vector3f32 pos, float width, float lenght, float depth, float height);
	void CreateTransitionWall(gce::Vector3f32 pos, float width, float lenght, float depth, float height, float lastYPos);
	void CreateHurtZone(gce::Vector3f32 pos, float width, float lenght, float depth);
	void AddBoxGeometry(gce::Vector3f32 pos, gce::Vector3f32 scaling, int textureIndex, BoxTag tag = COLLIDER);

	static std::vector<std::shared_ptr<sr::Texture>> s_tileTextures;
	std::vector<std::string> m_texture;
	bool m_initPath = false;

	std::vector<Obstacle*> m_obstacles;
	SceneGamePlay* m_sceneGamePlay;
	Obstacle* m_obstacle;
	PowerUp* m_powerUp;
};


