#ifndef __1000POINT_H__
#define __1000POINT_H__
#include "DynamicObject.h"
#include "Ninja.h"
class Point1000 : public DynamicObject
{
public:
	Point1000();
	CPhysicDx9*			getPhysic() const { return m_Physic; }
	Point1000(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~Point1000();
};
#endif