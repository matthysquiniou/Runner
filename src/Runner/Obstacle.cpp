#include "Obstacle.h"
#include "GameManager.h"
#include "Mesh.h"
#include "Box.h"
#include "EntityManager.h"
#include <iostream>

std::vector<std::shared_ptr<sr::Texture>> Obstacle::m_obstacleTextures;
static bool s_texturesInitialized = false;


Obstacle::Obstacle(gce::Vector3f32 position, gce::Vector3f32 scale, ObstacleTag tag)
    : Entity(InitMesh()), m_tilePosition(position), m_tileScale(scale)
{
    if (!s_texturesInitialized) {
        s_texturesInitialized = true;
    }

    m_entityManager = SceneManager::GetInstance()->GetScene(TagScene::GAMEPLAY)->GetEntityManager();

    if (tag == ObstacleTag::SIZEOBSTACLE) {
        GenerateRandomObstacle();
    }
    else {
        m_obstacleTag = tag;
        GenerateObstacle();
    }
}

Mesh* Obstacle::InitMesh() {
    Mesh* mesh = new Mesh();
    return mesh;
}

void Obstacle::GenerateRandomVelocity()
{
    int randomInt = rand();
    float velocityX = static_cast<float>(randomInt % 15);
    float velocityY = static_cast<float>(randomInt % 8);
    m_velocity = { velocityX, velocityY, 0.f };
}

void Obstacle::GenerateRandomObstacle()
{
    int randNumber = rand();
    if (randNumber % 100 > 30)
        return;
    int obstacleIndex = randNumber % static_cast<int>(ObstacleTag::SIZEOBSTACLE);
    m_obstacleTag = static_cast<ObstacleTag>(obstacleIndex);
    GenerateObstacle();
}

void Obstacle::GenerateRandomPos(float x, float y) {

    int ix = static_cast<int>(x);
    int iy = static_cast<int>(y);

    if (ix <= 0) ix = 1;
    if (iy <= 0) iy = 1;

    m_randomPos.x = static_cast<float>(rand() % ix) - x * 0.5f;
    m_randomPos.y = static_cast<float>(rand() % iy) + y * 0.5f;

    if (m_randomPos.y < y / 4.f)
        m_randomPos.y += y / 4.f;

    if (m_randomPos.y > y / 2.f)
        m_randomPos.y -= y / 4.f;
}

void Obstacle::GenerateObstacle()
{
    switch (m_obstacleTag)
    {

    case BLOCK: {

        gce::Vector3f32 ownScale = m_tileScale * 0.2f;
        gce::Vector3f32 ownPosition = { m_tilePosition.x, m_tilePosition.y + 5.f, m_tilePosition.z };
        AddBoxObstacle(ownScale, ownPosition);

        break;
    }
    case BLOCKMOVING: {

        gce::Vector3f32 ownScale = { 8.f, 8.f, 8.f };
        gce::Vector3f32 ownPosition = { m_tilePosition.x, m_tilePosition.y + 10.f, m_tilePosition.z };
        AddBoxObstacle(ownScale, ownPosition, true);

        GenerateRandomVelocity();

        break;
    }
    case COPYCAT: {

        gce::Vector3f32 ownScale = { 8.f, 8.f, 8.f };
        gce::Vector3f32 ownPosition = { m_tilePosition.x, m_tilePosition.y + 10.f, m_tilePosition.z };
        AddBoxObstacle(ownScale, ownPosition, false, true);

        break;
    }
    case MISSILE: {
        GenerateRandomPos(m_tileScale.x, m_tileScale.y);

        gce::Vector3f32 ownScale = { 2.f, 2.f, 8.f };
        gce::Vector3f32 ownPosition = { m_tilePosition.x + m_randomPos.x, m_tilePosition.y + m_randomPos.y, m_tilePosition.z };
        AddBoxObstacle(ownScale, ownPosition);

        break;
    }

    case LASER: {

        gce::Vector3f32 ownScale = { 2.f, 2.f, 2.f };
        gce::Vector3f32 ownPosition1 = { m_tilePosition.x + m_tileScale.x * 0.3f, m_tilePosition.y + 10.f, m_tilePosition.z };
        gce::Vector3f32 ownPosition2 = { m_tilePosition.x - m_tileScale.x * 0.3f, m_tilePosition.y + 10.f, m_tilePosition.z };

        AddBoxObstacle(ownScale, ownPosition1);
        AddBoxObstacle(ownScale, ownPosition2);

        break;
    }
    default:
        break;
    }
}

void Obstacle::ObstacleAnimation(float deltaTime)
{
    switch (m_obstacleTag) {
    }
}

void Obstacle::AddBoxObstacle(gce::Vector3f32 scale, gce::Vector3f32 position, bool hasCollision, bool hasHitBox)
{
    sr::Cube* geometry = GameManager::GetGeometryPool().Acquire<sr::Cube>();
    geometry->SetScale(scale);
    geometry->SetPosition(position);
	geometry->SetColor({1.0f, 0.0f, 0.0f});

    Box* hurtBox = new Box(BoxTag::HURT, position, scale);
    m_boxes.push_back(hurtBox);

    if (hasCollision) {
        Box* collisionBox = new Box(BoxTag::COLLIDER, position, scale);
        m_boxes.push_back(collisionBox);
    }

    if (hasHitBox) {
        Box* hitBox = new Box(BoxTag::HIT, position, scale);
        m_boxes.push_back(hitBox);
    }


    if (m_mesh)
        m_mesh->AddGeometry(geometry);
}

void Obstacle::Update(float deltaTime)
{
    switch (m_obstacleTag)
    {

    case BLOCKMOVING:
        Translate(m_velocity * deltaTime);
        break;

    case COPYCAT:
        if (m_character == nullptr)
        {
            std::vector<Entity*> charcaterVector = m_entityManager->GetEntitiesOfTag(EntityTag::CHARACTER);
            if (charcaterVector.size() == 0)
                break;
            m_character = charcaterVector[0];
        }
        gce::Vector3f32 pos = getPosition() - m_character->getPosition();
        gce::Vector3f32 deltaPos = { pos.x,pos.y, 0.0f };
        Translate(-deltaPos);
        {
            break;

    case LASER: {
        if (m_character == nullptr)
        {
            std::vector<Entity*> charcaterVector = m_entityManager->GetEntitiesOfTag(EntityTag::CHARACTER);
            if (charcaterVector.size() == 0)
                break;
            m_character = charcaterVector[0];
        }
        float deltaZPos = getPosition().z - m_character->getPosition().z;
        if (deltaZPos < 40.f && !m_laserActivationFlag)
        {
            m_laserActivationFlag = true;
            gce::Vector3f32 ownScale = { m_tileScale.x * 0.6f, 2.f, 2.f };
            gce::Vector3f32 ownPosition = { m_tilePosition.x , m_tilePosition.y + 10.f, m_tilePosition.z };
            AddBoxObstacle(ownScale, ownPosition);
        }
        m_rotation.x = 100.f / deltaZPos;
        Rotate(m_rotation * deltaTime);
        break;
    }
    case MISSILE:
        GenerateRandomPos(m_tilePosition.x, m_tilePosition.y);
        GenerateRandomVelocity();
        m_velocity = { 0.0f, 0.0f, -10.0f };

        Translate(m_velocity * deltaTime);
        break;
	default:
		break;

        }
    }
}

EntityTag Obstacle::GetTag() const {
    return EntityTag::OBSTACLE;
}


void Obstacle::Collide(gce::Vector3f32 penetration, BoxTag ownBoxTag, Entity* targetEntity, BoxTag targetBoxTag) {
    if (targetEntity->GetTag() == EntityTag::TILE && targetBoxTag == BoxTag::COLLIDER)
    {
        if (std::abs(penetration.y) < std::abs(penetration.x) && std::abs(penetration.y) < std::abs(penetration.z)) {
            //collision Y
            Translate({ 0.f,penetration.y,0.f });
            m_velocity.y *= -1;

        }
        else if (std::abs(penetration.x) < std::abs(penetration.y)) {
            //collision X
            Translate({ penetration.x,0.f,0.f });
            m_velocity.x *= -1;
        }
    }
    if (targetEntity->GetTag() == EntityTag::BULLET && targetBoxTag == BoxTag::HURT) {
		m_dead = true;
    }
}