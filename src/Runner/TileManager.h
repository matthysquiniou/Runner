#pragma once
#include "Tile.h"
#include "TileTag.h"

class EntityManager;
class SceneGamePlay;

class TileManager
{
public:
	TileManager(SceneGamePlay* scene, EntityManager* entityManager);
	//~TileManager() = default;

	void InitTileManager();
	void regenerateTiles();

private:
	TileTag choosingTile();
	float ChooseHeightVariation();
private:
	const float m_tileDefaultLenght = 50.0f;
	const float m_tileDefaultWidth = 50.0f;
	const float m_tileDefaultDepth = 1.0f;
	const float m_tileDefaultHeight = 50.f;
	const float m_minPathLenght = m_tileDefaultLenght * 20.0f; // chemin de 20 tiule de base de long
	const int m_yTileMaxVariation = 10.f;
	const int m_yTileMinVariation = 3.f;

	float m_currentPathLenght = 0.0f;
	const int m_scorePerTile = 15;

	float m_lastTileZPos = 0.0f;
	float m_lastTileYPos = 0.f;
	TileTag m_lastTileTag = STRAIGHT;

	EntityManager* m_entityManager;
	SceneGamePlay* m_scene;
};
