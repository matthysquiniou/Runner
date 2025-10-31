#include "pch.h"
#include "Tile.h"
#include "Mesh.h"
#include "GameManager.h"
#include "Box.h"
#include "BoxTag.h"
#include "Obstacle.h"
#include <iostream>
#include "PowerUp.h"
#include "SceneManager.h"
#include "SceneGamePlay.h"

#define LAVE_PATH 0
#define ROUTE_PATH 1
#define ROUTE_ROTATED_PATH 2
#define ROUTE_DROITE_PATH 3
#define ROUTE_GAUCHE_PATH 4
#define ROUTE_GOUDRON_PATH 5
#define ROUTE_INTERSECTION_PATH 6
#define ROUTE_INTERSECTION_ROTATED_PATH 7
#define ROUTE_VIRAGE_DROITE_PATH 8
#define ROUTE_VIRAGE_DROITE_ALT_PATH 9
#define ROUTE_VIRAGE_GAUCHE_PATH 10
#define ROUTE_VIRAGE_GAUCHE_ALT_PATH 11


std::vector<std::shared_ptr<sr::Texture>> Tile::s_tileTextures;
static bool s_texturesInitialized = false;

void Tile::GenerateTexturePaths()
{
	s_tileTextures.push_back(std::make_shared<sr::Texture>("res/Textures/BorderTextures/Lave.png")); 

	s_tileTextures.push_back(std::make_shared<sr::Texture>("res/Textures/RoutesTextures/Route.png"));
	s_tileTextures.push_back(std::make_shared<sr::Texture>("res/Textures/RoutesTextures/Route_Rotated.png"));
	s_tileTextures.push_back(std::make_shared<sr::Texture>("res/Textures/RoutesTextures/Route_Droite.png"));
	s_tileTextures.push_back(std::make_shared<sr::Texture>("res/Textures/RoutesTextures/Route_Gauche.png"));
	s_tileTextures.push_back(std::make_shared<sr::Texture>("res/Textures/RoutesTextures/Route_Goudron.png"));
	s_tileTextures.push_back(std::make_shared<sr::Texture>("res/Textures/RoutesTextures/Route_Intersection.png"));
	s_tileTextures.push_back(std::make_shared<sr::Texture>("res/Textures/RoutesTextures/Route_Intersection_Rotated.png"));
	s_tileTextures.push_back(std::make_shared<sr::Texture>("res/Textures/RoutesTextures/Route_Virage_Droite.png"));
	s_tileTextures.push_back(std::make_shared<sr::Texture>("res/Textures/RoutesTextures/Route_Virage_Droite_Alt.png"));
	s_tileTextures.push_back(std::make_shared<sr::Texture>("res/Textures/RoutesTextures/Route_Virage_Gauche.png"));
	s_tileTextures.push_back(std::make_shared<sr::Texture>("res/Textures/RoutesTextures/Route_Virage_Gauche_Alt.png"));
}


Mesh* Tile::InitMesh() {
	Mesh* mesh = new Mesh();
	return mesh;
}

Tile::Tile(TileTag tt, gce::Vector3f32 pos, float width, float lenght, float depth, float height, float lastHeight, bool isFirstTile) :Entity(InitMesh())
{
	CreateTiles(tt, pos, width, lenght, depth, height, lastHeight, isFirstTile);
}

void Tile::AddTextureTilt(std::string path)
{
	m_texture.push_back(path);
}

void Tile::AddBoxGeometry(gce::Vector3f32 pos, gce::Vector3f32 scaling, int textureIndex, BoxTag tag)
{
	sr::Cube* geometry = GameManager::GetGeometryPool().Acquire<sr::Cube>();
	geometry->SetScale(scaling);
	geometry->SetPosition(pos);
	if (textureIndex >= 0 && static_cast<size_t>(textureIndex) < s_tileTextures.size())
		geometry->SetTexture(*s_tileTextures[textureIndex]);

	// And their Collisions
	Box* collisionBox = new Box(tag, pos, scaling);
	m_boxes.push_back(collisionBox);

	m_mesh->AddGeometry(geometry);
}


void Tile::CreateTiles(TileTag tt, gce::Vector3f32 pos, float width, float lenght, float depth, float height, float lastYPos, bool isFirstTile)
{
	if (!s_texturesInitialized) {
		GenerateTexturePaths();
		s_texturesInitialized = true;
	}

	SceneManager* sm = SceneManager::GetInstance();
	Scene* baseScene = sm ? sm->GetScene(TagScene::GAMEPLAY) : nullptr;
	SceneGamePlay* gameplay = baseScene ? dynamic_cast<SceneGamePlay*>(baseScene) : nullptr;
	float diff = gameplay ? gameplay->GetDifficultyMultiplier() : 1.0f;
	int obstacleCount = static_cast<int>(diff);

	switch (tt)
	{
		case STRAIGHT:
		case LEFT:
		case RIGHT:
		case AROUND:
		case BROKENBRIDGE:
		case LEFTRIGHT:
		case STRAIGHTDOUBLE:
			break;
		default:
			std::cerr << "TileTag non g�r� dans CreateTiles Tile.cpp" << std::endl;
			return;
	}
	switch (tt)
	{
	case STRAIGHT:
	{
		AddBoxGeometry(
			{ pos.x - 0.1f * width, pos.y, pos.z - 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_GAUCHE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.1f * width, pos.y, pos.z - 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_GAUCHE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.1f * width, pos.y, pos.z - 0.0f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_GAUCHE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.1f * width, pos.y, pos.z + 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_GAUCHE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.1f * width, pos.y, pos.z + 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_GAUCHE_PATH);


		AddBoxGeometry(
			{ pos.x + 0.1f * width, pos.y, pos.z - 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_DROITE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.1f * width, pos.y, pos.z - 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_DROITE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.1f * width, pos.y, pos.z - 0.0f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_DROITE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.1f * width, pos.y, pos.z + 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_DROITE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.1f * width, pos.y, pos.z + 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_DROITE_PATH);


		if (!isFirstTile)
		{
			for (int i = 0; i <= obstacleCount; ++i) {
				m_obstacles.push_back(new Obstacle(
					{ pos.x, pos.y, pos.z },
					{ width, depth, lenght }));
			}
		}
		break;
	}

	case RIGHT:
	{
		AddBoxGeometry(
			{ pos.x - 0.2f * width, pos.y, pos.z - 0.4f*lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.2f * width, pos.y, pos.z - 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.2f * width, pos.y, pos.z },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.2f * width, pos.y, pos.z + 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.2f * width, pos.y, pos.z + 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_VIRAGE_DROITE_ALT_PATH);

		AddBoxGeometry(
			{ pos.x , pos.y, pos.z + 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_ROTATED_PATH);

		AddBoxGeometry(
			{ pos.x +0.2f * width, pos.y, pos.z + 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_ROTATED_PATH);


		for (int i = 0; i <= obstacleCount; ++i) {
			m_obstacles.push_back(new Obstacle(
				{ pos.x, pos.y, pos.z },
				{ width, depth, lenght }));
		}
		break;
	}

	case LEFT:
	{
		AddBoxGeometry(
			{ pos.x + 0.2f * width, pos.y, pos.z - 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.2f * width, pos.y, pos.z - 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.2f * width, pos.y, pos.z },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.2f * width, pos.y, pos.z + 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.2f * width, pos.y, pos.z + 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_VIRAGE_GAUCHE_ALT_PATH);

		AddBoxGeometry(
			{ pos.x , pos.y, pos.z + 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_ROTATED_PATH);

		AddBoxGeometry(
			{ pos.x - 0.2f * width, pos.y, pos.z + 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_ROTATED_PATH);

		m_powerUp = new PowerUp({ pos.x, pos.y + 5, pos.z });

		for (int i = 0; i <= obstacleCount; ++i) {
			m_obstacles.push_back(new Obstacle(
				{ pos.x, pos.y, pos.z },
				{ width, depth, lenght }));
		}
		break;
	}

	case AROUND:
	{
		AddBoxGeometry({ pos.x, pos.y, pos.z - 0.4f * lenght },
			{ width * 0.2f, depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry({ pos.x, pos.y, pos.z - 0.2f * lenght },
			{ width * 0.2f, depth, lenght * 0.2f },
			ROUTE_INTERSECTION_ROTATED_PATH);


		//left path


		AddBoxGeometry({ pos.x - 0.2f * width, pos.y, pos.z - 0.2f * lenght },
			{ width * 0.2f, depth, lenght * 0.2f },
			ROUTE_VIRAGE_DROITE_PATH);

		AddBoxGeometry({ pos.x - 0.2f * width, pos.y, pos.z  },
			{ width * 0.2f, depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry({ pos.x - 0.2f * width, pos.y, pos.z + 0.2f * lenght },
			{ width * 0.2f, depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry({ pos.x - 0.2f * width, pos.y, pos.z + 0.4f * lenght },
			{ width * 0.2f, depth, lenght * 0.2f },
			ROUTE_VIRAGE_DROITE_ALT_PATH);

		//right path


		AddBoxGeometry({ pos.x + 0.2f * width, pos.y, pos.z - 0.2f * lenght },
			{ width * 0.2f, depth, lenght * 0.2f },
			ROUTE_VIRAGE_GAUCHE_PATH);

		AddBoxGeometry({ pos.x + 0.2f * width, pos.y, pos.z },
			{ width * 0.2f, depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry({ pos.x + 0.2f * width, pos.y, pos.z + 0.2f * lenght },
			{ width * 0.2f, depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry({ pos.x + 0.2f * width, pos.y, pos.z + 0.4f * lenght },
			{ width * 0.2f, depth, lenght * 0.2f },
			ROUTE_VIRAGE_GAUCHE_ALT_PATH);



		AddBoxGeometry({ pos.x, pos.y, pos.z + 0.4f * lenght },
			{ width * 0.2f, depth, lenght * 0.2f },
			ROUTE_INTERSECTION_PATH);




		m_powerUp = new PowerUp({ pos.x, pos.y + 5, pos.z });

		for (int i = 0; i <= obstacleCount; ++i) {
			m_obstacles.push_back(new Obstacle(
				{ pos.x, pos.y, pos.z },
				{ width, depth, lenght }));
		}
	}

	case BROKENBRIDGE:
	{
		AddBoxGeometry({ pos.x -0.2f * width, pos.y, pos.z - 0.4f * lenght },
			{ width * 0.2f, depth, lenght * 0.2f },
			ROUTE_GOUDRON_PATH);

		AddBoxGeometry({ pos.x - 0.0f * width, pos.y, pos.z - 0.4f * lenght },
			{ width * 0.2f, depth, lenght * 0.2f },
			ROUTE_GOUDRON_PATH);

		AddBoxGeometry({ pos.x + 0.2f * width, pos.y, pos.z - 0.4f * lenght },
			{ width * 0.2f, depth, lenght * 0.2f },
			ROUTE_GOUDRON_PATH);

		AddBoxGeometry({ pos.x - 0.2f * width, pos.y, pos.z + 0.4f * lenght },
			{ width * 0.2f, depth, lenght * 0.2f },
			ROUTE_GOUDRON_PATH);

		AddBoxGeometry({ pos.x - 0.0f * width, pos.y, pos.z + 0.4f * lenght },
			{ width * 0.2f, depth, lenght * 0.2f },
			ROUTE_GOUDRON_PATH);

		AddBoxGeometry({ pos.x + 0.2f * width, pos.y, pos.z + 0.4f * lenght },
			{ width * 0.2f, depth, lenght * 0.2f },
			ROUTE_GOUDRON_PATH);

		AddBoxGeometry({ pos.x - 0.1f * width, pos.y, pos.z - 0.2f * lenght },
			{ width * 0.2f, depth, lenght * 0.2f },
			ROUTE_GAUCHE_PATH);

		AddBoxGeometry({ pos.x + 0.1f * width, pos.y, pos.z + 0.2f * lenght },
			{ width * 0.2f, depth, lenght * 0.2f },
			ROUTE_DROITE_PATH);




		m_powerUp = new PowerUp({ pos.x, pos.y + 5, pos.z });

		for (int i = 0; i <= obstacleCount; ++i) {
			m_obstacles.push_back(new Obstacle(
				{ pos.x, pos.y, pos.z },
				{ width, depth, lenght }));
		}
		break;
	}

	case LEFTRIGHT:
	{
		AddBoxGeometry(
			{ pos.x - 0.2f * width, pos.y, pos.z -0.4f*lenght},
			{ width * 0.2f , depth, lenght *0.2f},
			ROUTE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.2f * width, pos.y, pos.z - 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.2f * width, pos.y, pos.z - 0.0f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.2f * width, pos.y, pos.z + 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.2f * width, pos.y, pos.z + 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_PATH);


		AddBoxGeometry(
			{ pos.x + 0.2f * width, pos.y, pos.z - 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.2f * width, pos.y, pos.z - 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.2f * width, pos.y, pos.z - 0.0f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.2f * width, pos.y, pos.z + 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.2f * width, pos.y, pos.z + 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_PATH);

		for (int i = 0; i <= obstacleCount; ++i) {
			m_obstacles.push_back(new Obstacle(
				{ pos.x, pos.y, pos.z },
				{ width, depth, lenght }));
		}
		break;
	}

	case STRAIGHTDOUBLE:
	{
		AddBoxGeometry(
			{ pos.x - 0.1f * width, pos.y, pos.z - 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_GAUCHE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.1f * width, pos.y, pos.z - 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_GAUCHE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.1f * width, pos.y, pos.z - 0.0f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_GAUCHE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.1f * width, pos.y, pos.z + 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_GAUCHE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.1f * width, pos.y, pos.z + 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_GAUCHE_PATH);


		AddBoxGeometry(
			{ pos.x + 0.1f * width, pos.y, pos.z - 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_DROITE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.1f * width, pos.y, pos.z - 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_DROITE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.1f * width, pos.y, pos.z - 0.0f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_DROITE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.1f * width, pos.y, pos.z + 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_DROITE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.1f * width, pos.y, pos.z + 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_DROITE_PATH);

		//Second Floor
		AddBoxGeometry(
			{ pos.x - 0.1f * width, pos.y + 20.0f, pos.z - 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_GAUCHE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.1f * width, pos.y + 20.0f, pos.z - 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_GAUCHE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.1f * width, pos.y + 20.0f, pos.z - 0.0f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_GAUCHE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.1f * width, pos.y + 20.0f, pos.z + 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_GAUCHE_PATH);

		AddBoxGeometry(
			{ pos.x - 0.1f * width, pos.y + 20.0f, pos.z + 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_GAUCHE_PATH);


		AddBoxGeometry(
			{ pos.x + 0.1f * width, pos.y + 20.0f, pos.z - 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_DROITE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.1f * width, pos.y + 20.0f, pos.z - 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_DROITE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.1f * width, pos.y + 20.0f, pos.z - 0.0f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_DROITE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.1f * width, pos.y + 20.0f, pos.z + 0.2f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_DROITE_PATH);

		AddBoxGeometry(
			{ pos.x + 0.1f * width, pos.y + 20.0f, pos.z + 0.4f * lenght },
			{ width * 0.2f , depth, lenght * 0.2f },
			ROUTE_DROITE_PATH);

		for (int i = 0; i <= obstacleCount; ++i) {
			m_obstacles.push_back(new Obstacle(
				{ pos.x, pos.y, pos.z },
				{ width, depth, lenght }));
		}
		break;
	}

	default:
		break;
	}
	CreateCeillingAndWall(pos, width, lenght, depth, height);
	CreateTransitionWall(pos, width, lenght, depth, height, lastYPos);
	CreateHurtZone(pos, width, lenght, depth);
}

void Tile::Update(float deltaTime) 
{

}

EntityTag Tile::GetTag() const{
	return EntityTag::TILE;
}

void Tile::RegisterChildrenWithManager(EntityManager* em)
{
	if (!em) return;

	if (m_powerUp)
		em->AddEntityBuffer(m_powerUp);

	for (Obstacle* obs : m_obstacles) {
		if (obs)
			em->AddEntityBuffer(obs);
	}
}
void Tile::CreateCeillingAndWall(gce::Vector3f32 pos, float width, float lenght, float depth, float height) {
	AddBoxGeometry({ pos.x - 0.3f * width - 0.5f, pos.y + height * 0.5f, pos.z},
		{ depth, height, lenght },
		ROUTE_GOUDRON_PATH);
	AddBoxGeometry({ pos.x + 0.3f * width + 0.5f, pos.y + height * 0.5f, pos.z},
		{ depth, height, lenght },
		ROUTE_GOUDRON_PATH);
	AddBoxGeometry({ pos.x, height + pos.y, pos.z},
		{ width * 0.6f, depth, lenght },
		ROUTE_GOUDRON_PATH);
}

void Tile::CreateTransitionWall(gce::Vector3f32 pos, float width, float lenght, float depth, float height, float lastYPos) {
	AddBoxGeometry({ pos.x, (pos.y + lastYPos - depth) * 0.5f, pos.z - (lenght - depth) * 0.5f },
		{ width * 0.6f, std::abs(pos.y - lastYPos), depth},
		ROUTE_GOUDRON_PATH, BoxTag::HURT);
	AddBoxGeometry({ pos.x, (pos.y + lastYPos) * 0.5f + height, pos.z - (lenght - depth) * 0.5f },
		{ width * 0.6f, std::abs(pos.y - lastYPos), depth },
		ROUTE_GOUDRON_PATH, BoxTag::HURT);
}

void Tile::CreateHurtZone(gce::Vector3f32 pos, float width, float lenght, float depth) {
	AddBoxGeometry({ pos.x, pos.y - 1.f, pos.z},
		{ width * 2, depth, lenght },
		LAVE_PATH, BoxTag::HURT);

	Box* collisionBox = new Box(BoxTag::COLLIDER,
		{ pos.x, pos.y - 2.f, pos.z },
		{ width * 2, depth, lenght });
	m_boxes.push_back(collisionBox);
}