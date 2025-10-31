#pragma once
#include "TagScene.h" 

class Camera;
class EntityManager;

class Scene
{
public:

    Scene();
    virtual ~Scene();

    virtual void Init();
    virtual void Update(float deltaTime);
    virtual void Render();

	void EmptyEntityBuffer();

	virtual TagScene GetTag() const = 0;

    EntityManager* GetEntityManager() const { return m_entityManager; }

protected:

    EntityManager* m_entityManager;

};
