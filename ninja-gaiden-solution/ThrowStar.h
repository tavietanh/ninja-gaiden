#ifndef THROWSTAR_H
#define THROWSTAR_H
#include "DynamicObject.h"
#include "Ninja.h"
class ThrowStar : public DynamicObject
{
public:
	ThrowStar();
	CPhysicDx9*			getPhysic() const { return m_Physic; }
	ThrowStar(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~ThrowStar();
};

#endif
