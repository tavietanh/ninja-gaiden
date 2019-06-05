#ifndef __FLAMES_H__
#define __FLAMES_H__
#include "DynamicObject.h"
#include "Ninja.h"
class Flames : public DynamicObject
{
public:
	Flames();
	CPhysicDx9*			getPhysic() const { return m_Physic; }
	Flames(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~Flames();
};

#endif