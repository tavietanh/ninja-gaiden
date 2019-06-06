#ifndef __FivePower_H__
#define __FivePower_H__
#include "DynamicObject.h"
#include "Ninja.h"
class FivePower : public DynamicObject
{
public:
	FivePower();
	CPhysicDx9*			getPhysic() const { return m_Physic; }
	FivePower(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~FivePower();
};
#endif