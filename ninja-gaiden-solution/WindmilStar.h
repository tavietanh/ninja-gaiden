#ifndef WINDMILSTAR_H
#define WINDMILSTAR_H
#include "DynamicObject.h"
#include "Ninja.h"
class WindMilStar : public DynamicObject
{
public:
	WindMilStar();
	CPhysicDx9*			getPhysic() const { return m_Physic; }
	WindMilStar(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~WindMilStar();
};

#endif
