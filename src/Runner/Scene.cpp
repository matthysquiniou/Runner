#include "Scene.h"
#include "GameManager.h"
#include "EntityManager.h"
#include "Mesh.h"
#include "Character.h"
#include "GCSR.h"
#include "SceneGamePlay.h"

Scene::Scene()
    : m_entityManager(nullptr)
{

}

Scene::~Scene()
{
    delete m_entityManager;
    m_entityManager = nullptr;
}

void Scene::Init()
{
    
    if (!m_entityManager) {
        m_entityManager = new EntityManager();
    }
}

void Scene::Update(float deltaTime)
{
    if (!m_entityManager) return;

    for (Entity* entity : m_entityManager->GetAllEntities())
    {
        entity->Update(deltaTime);
    }
}

void Scene::Render()
{
    for (Entity* entity : m_entityManager->GetAllEntities())
    {
        entity->Render();
    }
}

void Scene::EmptyEntityBuffer()
{
    m_entityManager->Add();
}
