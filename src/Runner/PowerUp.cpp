#include "PowerUp.h"
#include "Mesh.h"
#include "GameManager.h"
#include "Box.h"
#include "BoxTag.h"
#include "Character.h"
#include <iostream>
#include "Obstacle.h"

std::vector<std::shared_ptr<sr::Texture>> PowerUp::m_powerUpTextures;

static bool s_texturesInitialized = false;

PowerUp::PowerUp(gce::Vector3f32 position, PowerUpTag tag)
    : Entity(InitMesh()), m_position(position)
{
    if (!s_texturesInitialized) {
        GeneratePowerUpPaths();
        s_texturesInitialized = true;
    }

    m_rotationSpeed = 5.0f;
    m_bounceHeight = 0.5f;
    m_bounceSpeed = 2.0f;
    m_initialYPosition = m_position.y;
    m_elapsedTime = 0.0f;

    if (tag == PowerUpTag::POWER_SIZE) {
        GenerateRandomPowerUp();
    }
    else {
        m_powerTag = tag;
        GeneratePowerUp(static_cast<int>(tag));
    }
}

Mesh* PowerUp::InitMesh() {
    Mesh* mesh = new Mesh();
    return mesh;
}

void PowerUp::GeneratePowerUpPaths()
{
    m_powerUpTextures.clear();
    m_powerUpTextures.push_back(std::make_shared<sr::Texture>("res/Textures/BoostTextures/SpeedBoost.png"));
    m_powerUpTextures.push_back(std::make_shared<sr::Texture>("res/Textures/BoostTextures/JumpBoost.png"));
    m_powerUpTextures.push_back(std::make_shared<sr::Texture>("res/Textures/BoostTextures/FlyingBoost.png"));
    m_powerUpTextures.push_back(std::make_shared<sr::Texture>("res/Textures/BoostTextures/ScoreBoost.png"));
}

void PowerUp::Update(float deltaTime)
{
    if (m_dead)
        return;

    if (m_mesh)
        PowerUpAnimation(deltaTime);
}

void PowerUp::GenerateRandomPowerUp()
{
    int powerUpIndex = rand() % static_cast<int>(PowerUpTag::POWER_SIZE);
	int spawnRate = rand() % 100;

    if (spawnRate > 25)
        return;

    m_powerTag = static_cast<PowerUpTag>(powerUpIndex);
    GeneratePowerUp(powerUpIndex);
}

void PowerUp::GeneratePowerUp(int powerUpindex)
{
    m_powerTag = static_cast<PowerUpTag>(powerUpindex);

    AddBoxPowerUp(m_position, powerUpindex);
}

void PowerUp::PowerUpAnimation(float deltaTime)
{

    if (m_mesh) {
        m_mesh->Rotate({ 0.0f, m_rotationSpeed * deltaTime, 0.0f });
    } else {
        Rotate({ 0.0f, m_rotationSpeed * deltaTime, 0.0f });
    }

    m_elapsedTime += deltaTime;
    float newY = m_initialYPosition + m_bounceHeight * std::sin(m_bounceSpeed * m_elapsedTime);

    if (m_mesh) {
        gce::Vector3f32 center = m_mesh->GetCenter();
        gce::Vector3f32 desired = center;
        desired.y = newY;
        m_mesh->Translate(desired - center);
    }
}

void PowerUp::ActivePowerUpEffect(Entity* entity, PowerUpTag tag)
{
    if (m_dead) {
        std::cout << "PowerUp::ActivePowerUpEffect ignored (already consumed): this=" << this << std::endl;
        return;
    }

    if (Character* character = dynamic_cast<Character*>(entity)) {
        m_targetCharacter = character;
        ResetTimer();

        switch (tag) {
        case PowerUpTag::POWERUPSPEEDBOOST:
            character->SetSpeedBoostIsActive(true);
            character->SetAcceleration(static_cast<int>(character->GetAcceleration() * m_accelerationMultiplier));
            break;
        case PowerUpTag::POWERUPJUMPBOOST:
            character->SetJumpBoostIsActive(true);
            character->SetJumpHeightBoost(m_jumpHeightBoostValue);
            break;
        case PowerUpTag::POWERUPFLYINGBOOST:
            character->SetJetPackFuel(m_flyingBoostValue);
            character->SetFlyingBoostIsActive(true);
            break;
        case PowerUpTag::POWERUPSCOREBOOST:
            character->SetScoreBoostIsActive(true);
            break;
        default:
            break;
        }
        m_boxes.clear();
    }
}

void PowerUp::Collide(gce::Vector3f32 penetration, BoxTag ownBoxTag, Entity* targetEntity, BoxTag targetBoxTag) {
    if (targetEntity->GetTag() == EntityTag::CHARACTER && targetBoxTag == BoxTag::COLLIDER)
    {
        m_dead = true;
    }
}

void PowerUp::AddBoxPowerUp(gce::Vector3f32 pos, int textureIndex, gce::Vector3f32 scaling, BoxTag tag)
{
    sr::Cube* geometry = GameManager::GetGeometryPool().Acquire<sr::Cube>();
    geometry->SetScale(scaling);
    geometry->SetPosition(pos);

    if (textureIndex >= 0 && static_cast<size_t>(textureIndex) < m_powerUpTextures.size())
        geometry->SetTexture(*m_powerUpTextures[textureIndex]);

    Box* collisionBox = new Box(tag, pos, scaling);

    m_boxes.push_back(collisionBox);
    m_mesh->AddGeometry(geometry);
}

EntityTag PowerUp::GetTag() const {
    return EntityTag::POWERUP;
}
