#ifndef HEALTH_H
#define HEALTH_H
#include "DynamicObject.h"
#include "Ninja.h"
class Health : public DynamicObject
{
public:
	Health();
	CPhysicDx9*			getPhysic() const { return m_Physic; }
	Health(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~Health();
};
#endif