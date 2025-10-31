#include "Character.h"
#include "EntityManager.h"
#include "GameManager.h"
#include "Mesh.h"
#include "Texture.h"
#include <memory>
#include "Physics.h"
#include "Box.h"
#include <algorithm>
#include "Shoot.h"
#include <iostream>
#include "PowerUp.h"
#include "GameManager.h"
#include "Controller.h"

Character::Character(Mesh* mesh, float speed, EntityManager* entityManager, Camera* camera)
    : Entity(mesh),
    m_mesh(mesh),
    m_speed(speed),
    m_camera(camera),
    m_entityManager(entityManager)
{
    m_rotation = { 0.f, 0.f, 0.f };
    float currentZRotation = 0.0f;

    sr::SetMousePosition({ static_cast<int>(1920 * 0.5f),static_cast<int>(1080 * 0.5f) });

    m_position = { 0.f, 1.1f, 0.0f };
    m_scale = { 0.75f, 1.0f, 1.0f };

    m_texture = std::make_shared<sr::Texture>("res/Obj/Orc.png");

    sr::Custom* player = GameManager::GetOrcPool().Acquire<sr::Custom>("res/Obj/Orc.obj");

    player->SetPosition(m_position);
    player->SetRotation({ 0.0f, 0.0f, 0.0f });
    player->SetScale(m_scale);

    player->SetTexture(*m_texture);

    gce::Vector3f32 scaleBox = { 3.f, 6.f, 2.f };
    gce::Vector3f32 postionBox = { 0.f, 3.f, 1.f };
    postionBox += m_position;
    Box* collisionBox = new Box(BoxTag::COLLIDER, postionBox, scaleBox);
    Box* hitBox = new Box(BoxTag::HIT, postionBox, scaleBox);

    m_boxes.push_back(collisionBox);
    m_boxes.push_back(hitBox);

    if (m_mesh)
        m_mesh->AddGeometry(player);

    if (entityManager)
        entityManager->AddEntityBuffer(this);

    m_JetPackFuel = m_MaxJetPackFuel;

    m_physics = new Physics();
    m_velocity.z = m_speed;
}

void Character::Update(float deltaTime)
{
    m_rotation = { 0.f, 0.f, 0.f };

    Translate(m_velocity * deltaTime);
    m_physics->Update(this, deltaTime);

    // gun firerate 
    if (m_currentReload > 0.0f)
    {
        m_currentReload -= deltaTime;
        if (m_currentReload < 0.0f)
            m_currentReload = 0.0f;
    }

    // recharge jetpack
    if (m_isGrounded && GetJetPackFuel() < m_MaxJetPackFuel)
    {
        m_JetPackFuel += m_JetPackFuelRecharge;
    }

    if (GetJetPackFuel() >= m_MaxJetPackFuel && GetFlyingBoostIsActive() == false)
    {
        m_JetPackFuel = m_MaxJetPackFuel;
    }

    if (GetJetPackFuel() < 0)
    {
        m_JetPackFuel = 0;
    }

    // Power-up timer update
    if (m_activePowerUpTimer > 0.0f)
    {
        m_activePowerUpTimer -= deltaTime;
        if (m_activePowerUpTimer <= 0.0f)
        {
            m_activePowerUpTimer = 0.0f;
            SetScoreBoostIsActive(false);
            SetSpeedBoostIsActive(false);
            SetFlyingBoostIsActive(false);
            SetJumpBoostIsActive(false);

            SetPowerUpActive(false);
            m_acceleration = 0.0f;
        }
    }

    //check if charcater is dead
    if (m_isAlive == false)
    {
        Character::DeathSequence(deltaTime);
    }

    RotatePlayer(m_rotation);
}

void Character::Translate(gce::Vector3f32 offset) {
    Entity::Translate(offset);
    m_camera->SetPositionWithOffSet(Entity::getPosition());
}

void Character::RotatePlayer(gce::Vector3f32 rotation)
{
    Entity::Rotate(-rotation);
}

EntityTag Character::GetTag() const {
    return EntityTag::CHARACTER;
}

void Character::Collide(gce::Vector3f32 penetration, BoxTag ownBoxTag, Entity* targetEntity, BoxTag targetBoxTag) {
    if (targetEntity->GetTag() == EntityTag::TILE && targetBoxTag == BoxTag::COLLIDER)
    {
        if (std::abs(penetration.y) < std::abs(penetration.x) && std::abs(penetration.y) < std::abs(penetration.z)) {
            //collision Y
            Translate({ 0.f,penetration.y,0.f });
            if (penetration.y > 0.f)
            {
                m_velocity.y = 0.f;
                m_isGrounded = true;
            }
            else {
                m_velocity.y *= -0.3f;
            }
        }
        else if (std::abs(penetration.x) < std::abs(penetration.y)) {
            //collision X
            Translate({ penetration.x,0.f,0.f });
        }
        else {
            Translate({ 0.f, 0.f, penetration.z });
            //merci google trad
            const float deathThreshold = 5.0f;
            if (std::abs(penetration.z) > deathThreshold) m_isAlive = false;
        }
    }
    if (targetEntity->GetTag() == EntityTag::TILE && targetBoxTag == BoxTag::HURT)
    {
        m_isAlive = false;
    }
    if (targetEntity->GetTag() == EntityTag::OBSTACLE && targetBoxTag == BoxTag::HURT)
    {
        m_isAlive = false;
    }
    if (targetEntity->GetTag() == EntityTag::POWERUP && targetBoxTag == BoxTag::COLLIDER)
    {
        if (PowerUp* pu = dynamic_cast<PowerUp*>(targetEntity)) {
            pu->ActivePowerUpEffect(this, pu->GetPowerTag());
            SetPowerUpScoreMultiplier(pu->GetPowerUpScoreMultiplier());

            switch (pu->GetPowerTag())
            {
            case PowerUpTag::POWERUPSPEEDBOOST:
                m_speedBoostActive = true;
                SetSpeedBoostIsActive(true);
                std::cout << "Speed PowerUp Activated." << std::endl;
                break;
            case PowerUpTag::POWERUPJUMPBOOST:
                m_jumpBoostActive = true;
                SetJumpBoostIsActive(true);
                std::cout << "Jump PowerUp Activated." << std::endl;
                break;
            case PowerUpTag::POWERUPFLYINGBOOST:
                m_flyingBoostActive = true;
                SetFlyingBoostIsActive(true);
                std::cout << "Flying PowerUp Activated." << std::endl;
                break;
            case PowerUpTag::POWERUPSCOREBOOST:
                scoreBoostActive = true;
                SetScoreBoostIsActive(true);
                std::cout << "Score PowerUp Activated." << std::endl;
                break;
            default:
                std::cout << "PowerUp Activated!" << std::endl;
                break;
            }
        }
    }
}

void Character::DeathSequence(float deltaTime) {
    // stop the character
    m_speed = 0.0f;
    m_velocity = { 0.0f,0.0f,0.0f };
    m_acceleration = 0;
    m_JetPackFuelRecharge = 0;
    m_JetPackFuel = 0;

    float fallDir = 1.0f;
    float targetAngle = 0.5f;


    // Make the Character falls to the side (death animation)
    if (getPosition().x > 0.0f) {
        fallDir = -1.0f;
        targetAngle = -0.5f;

        if (m_PlayerRotation.z > targetAngle * gce::PI) {
            m_rotation.z = fallDir * deltaTime;
            m_PlayerRotation.z += m_rotation.z;
        }
        else {
            SceneManager::GetInstance()->AddScene(TagScene::GAMEOVER);
            SceneManager::GetInstance()->RemoveScene(TagScene::GAMEPLAY, false, true);
        }
    }

    else {
        if (m_PlayerRotation.z < targetAngle * gce::PI) {
            m_rotation.z = fallDir * deltaTime;
            m_PlayerRotation.z += m_rotation.z;
        }
        else {
            SceneManager::GetInstance()->AddScene(TagScene::GAMEOVER);
            SceneManager::GetInstance()->RemoveScene(TagScene::GAMEPLAY, false, true);
        }
    }
}

void Character::MoveLeft(float deltaTime)
{
    m_velocity.x = -m_speed - m_acceleration * deltaTime;
    float targetAngle = -0.15f;
    if (m_PlayerRotation.y > targetAngle * gce::PI && m_isAlive == true) {
        m_rotation.y = -2.0f * deltaTime;
        m_PlayerRotation.y += m_rotation.y;
        Rotate(m_rotation);
    }
}

void Character::MoveRight(float deltaTime)
{
    m_velocity.x = m_speed + m_acceleration * deltaTime;
    float targetAngle = 0.15f;
    if (m_PlayerRotation.y < targetAngle * gce::PI && m_isAlive==true) {
        m_rotation.y = 2.0f * deltaTime;
        m_PlayerRotation.y += m_rotation.y;
        Rotate(m_rotation);
    }
}

void Character::LookAhead(float deltaTime)
{
    float targetAngle = 0.005f;
   if(m_isAlive==true){
    if (-targetAngle * gce::PI > m_PlayerRotation.y || targetAngle * gce::PI < m_PlayerRotation.y) {
        if (m_PlayerRotation.y > targetAngle * gce::PI) {
            m_rotation.y = -3.0f * deltaTime;
            m_PlayerRotation.y += m_rotation.y;
        }
        else if (m_PlayerRotation.y < -targetAngle * gce::PI) {
            m_rotation.y = 3.0f * deltaTime;
            m_PlayerRotation.y += m_rotation.y;
        }
    }else{
        m_rotation.y = 0.0f;
    }

    Rotate(m_rotation);
   }
}

void Character::Jump()
{
    m_velocity.y += m_jumpHeight + m_jumpHeightBoost;
    m_isGrounded = false;
}

void Character::JetPackUp(float deltaTime)
{
    if (m_JetPackFuel > 0.0f)
    {
        m_JetPackFuel -= 100.f * deltaTime;
        if (m_JetPackFuel < 0.f) m_JetPackFuel = 0.f;

        m_isGrounded = false;
        m_directionShoot = { 0.0f, -1.0f, 0.0f };
        m_velocity.y += m_velocityJetPack * deltaTime;

        if (m_JetPackFuel <= 25.0f)
            m_currentColor = m_red;
        else if (m_JetPackFuel <= 50.0f)
            m_currentColor = m_orange;
        else
            m_currentColor = m_white;

        m_shoot = new Shoot(m_entityManager, this, m_directionShoot, m_backOffSet + m_SpaceBetwinTrailOffSet, m_currentColor);
        m_shoot = new Shoot(m_entityManager, this, m_directionShoot, m_backOffSet - m_SpaceBetwinTrailOffSet, m_currentColor);
    }
}

void Character::JetPackDown(float deltaTime)
{
    if (m_JetPackFuel > 0.0f && m_isGrounded == false)
    {
        m_JetPackFuel -= 100.f * deltaTime;
        if (m_JetPackFuel < 0.f) m_JetPackFuel = 0.f;

        m_directionShoot = { 0.0f, -1.0f, 0.0f };
        m_velocity.y = m_velocityJetPack + m_acceleration * 0.1f;

        m_directionShoot = { 0.0f, 1.0f, 0.0f };
        m_velocity.y = -m_speed - m_acceleration;

        if (m_JetPackFuel <= 25.0f)
            m_currentColor = m_red;
        else if (m_JetPackFuel <= 50.0f)
            m_currentColor = m_orange;
        else
            m_currentColor = m_white;

        m_shoot = new Shoot(m_entityManager, this, m_directionShoot, m_backOffSet);
    }
}

void Character::ShootForward()
{
    if (m_currentReload <= 0.0f)
    {
        m_directionShoot = { 0.0f, 0.0f, 1.0f };
        m_currentReload = m_reloadTime;
        m_shoot = new Shoot(m_entityManager, this, m_directionShoot);
	}
}
