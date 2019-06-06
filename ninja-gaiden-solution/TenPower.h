#ifndef __10Power_H__
#define __10Power_H__
#include "DynamicObject.h"
#include "Ninja.h"
class TenPower : public DynamicObject
{
public:
	TenPower();
	CPhysicDx9*			getPhysic() const { return m_Physic; }
	TenPower(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~TenPower();
};
#endif
