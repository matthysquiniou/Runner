#include "pch.h"
#include "Tile.h"
#include "TileManager.h"
#include "EntityManager.h"
#include "SceneGamePlay.h"


TileManager::TileManager(SceneGamePlay* scene, EntityManager* entityManager)
	:m_entityManager(entityManager), m_scene(scene) 
{

}

void TileManager::InitTileManager() {

	
	Tile* firstTile = new Tile(STRAIGHT, { 0.0f, m_lastTileYPos, 0.0f }, m_tileDefaultWidth, m_tileDefaultLenght, m_tileDefaultDepth, m_tileDefaultHeight, m_lastTileYPos, true); // get a rand tile and place it correctly
	m_entityManager->AddEntityBuffer(firstTile);
	firstTile->RegisterChildrenWithManager(m_entityManager);
	TileTag randTile = STRAIGHT;
	m_currentPathLenght += m_tileDefaultLenght;

	int i = 0;
	srand(time(0) + i);

	while (m_currentPathLenght < m_minPathLenght) 
	{
		randTile = choosingTile();

		while (randTile == m_lastTileTag)
		{ 
			srand(time(0) + i);
			randTile = choosingTile();
			i++;
		}
		float heightVariation = ChooseHeightVariation();
		Tile* newTile = new Tile(randTile, { 0.0f, m_lastTileYPos + heightVariation, m_lastTileZPos + m_tileDefaultLenght }, m_tileDefaultWidth, m_tileDefaultLenght, m_tileDefaultDepth, m_tileDefaultHeight, m_lastTileYPos);
		m_lastTileYPos = m_lastTileYPos + heightVariation;
		m_entityManager->AddEntityBuffer(newTile);
		newTile->RegisterChildrenWithManager(m_entityManager);

		m_lastTileZPos += m_tileDefaultLenght;
		m_lastTileTag = randTile;
		m_currentPathLenght += m_tileDefaultLenght;
	}
}

TileTag TileManager::choosingTile() {
	// Choose a number between : 0 to 3 = SPECS, 4 = BRIDGE
	const int TileTagFirst = 0;
	const int TileTagLast = TileTag::TILETAGSIZE - 1;

	int randomNumber = TileTagFirst + (rand() % (TileTagLast - TileTagFirst + 1));
	return static_cast<TileTag>(randomNumber);
};

float TileManager::ChooseHeightVariation() {
	int randNumber = rand();
	bool isPositive = randNumber % 2;
	float variation = static_cast<float>(randNumber % m_yTileMaxVariation);
	if (variation < m_yTileMinVariation)
		variation = m_yTileMinVariation;

	return isPositive ? variation : variation * -1.f;
}

void TileManager::regenerateTiles() {

	std::vector<Entity*> entityCharacters = m_entityManager->GetEntitiesOfTag(EntityTag::CHARACTER); // get the character

	if (entityCharacters.size() == 0)
		return;

	Entity* character = entityCharacters[0];

	std::vector<Entity*> tileArray = m_entityManager->GetEntitiesOfTag(EntityTag::TILE);

	for (int i = 0; i < tileArray.size(); i++)
	{
		int j = 0;
		Entity* tile = tileArray[i];
		float tileZPos = tile->getPosition().z;
		//float tileLenght = tile->lenght;

		if (tileZPos < (character->getPosition().z - 2 * m_tileDefaultLenght)) { // check for Tile Far Behind Player
			m_lastTileZPos += m_tileDefaultLenght;
			m_currentPathLenght -= m_tileDefaultLenght;

			TileTag regenRandTile = choosingTile();

			while (regenRandTile == m_lastTileTag)
			{
				srand(time(0) + j);
				regenRandTile = choosingTile();
				j++;
			}

			float heightVariation = ChooseHeightVariation();
			Tile* regenTile = new Tile(regenRandTile, { 0.0f, m_lastTileYPos + heightVariation, m_lastTileZPos }, m_tileDefaultWidth, m_tileDefaultLenght, m_tileDefaultDepth, m_tileDefaultHeight, m_lastTileYPos);
			m_lastTileYPos = m_lastTileYPos + heightVariation;
			m_entityManager->AddEntityBuffer(regenTile);
			regenTile->RegisterChildrenWithManager(m_entityManager);

			m_lastTileTag = regenRandTile;
			tile->m_dead = true;
			m_scene->AddScore(m_scorePerTile);

		}
	}

	m_entityManager->RemoveDeadEntities();
}

