#include "pch.h"
#include "Entity.h"
#include "Mesh.h"
#include "Box.h"
#include "GameManager.h"

Entity::Entity(Mesh* mesh) : m_mesh(mesh) {}

Entity::~Entity() {
    delete m_mesh;
    m_mesh = nullptr;
    for (Box* box : m_boxes) {
        delete box;
    }
    m_boxes.clear();
}

void Entity::Render() {
    GameManager* gm = GameManager::GetInstance();
    if (!gm) return;
    if (!m_mesh) return;

    sr::Window& window = gm->GetWindow();
    m_mesh->Render(&window);
}


void Entity::Translate(gce::Vector3f32 translation) {
    m_mesh->Translate(translation);
    for (size_t i = 0; i < m_boxes.size(); i++)
    {
        Box* box = m_boxes[i];
        box->Translate(translation);
    }
    
}

void Entity::Rotate(gce::Vector3f32 rotation) {
    m_mesh->Rotate(rotation);
}

void Entity::Collide(gce::Vector3f32 penetration, BoxTag ownBoxTag, Entity* targetEntity, BoxTag targetBoxTag) {}

EntityTag Entity::GetTag() const {
    return EntityTag::ENTITY;
}

bool Entity::IsDead() const {
    return m_dead;
}

std::vector<Box*>& Entity::getBoxs() {
    return m_boxes;
}

gce::Vector3f32 Entity::getPosition() {
    return m_mesh->GetCenter();
}

float Entity::getWeight() const {
    return m_weight;
}