#ifndef __500POINT_H__
#define __500POINT_H__
#include "DynamicObject.h"
#include "Ninja.h"
class Point500 : public DynamicObject
{
public:
	Point500();
	CPhysicDx9*			getPhysic() const { return m_Physic; }
	Point500(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~Point500();
};
#endif