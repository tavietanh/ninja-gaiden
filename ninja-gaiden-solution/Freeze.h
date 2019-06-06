#ifndef FREEZE_H
#define FREEZE_H
#include "DynamicObject.h"
#include "Ninja.h"
class Freeze : public DynamicObject
{
public:
	Freeze();
	CPhysicDx9*			getPhysic() const { return m_Physic; }
	Freeze(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~Freeze();
};
#endif