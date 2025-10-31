#include "GCSR.h"

class Entity;
class Physics {
public:
	void Update(Entity* entity, float deltaTime);
private:
	inline static const float m_maxVelocity = 100.f;
	inline static const gce::Vector3f32 m_gravity = { 0.f, -19.62, 0.f };
};