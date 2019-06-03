#ifndef DYNAMICOBJECT
#define DYNAMICOBJECT

#include "CObjectDx9.h"
#include "Collision.h"
#include "CGameTimeDx9.h"
#include "EDirectAttack.h"


class Collision;

class DynamicObject :
	public CObjectDx9
{
protected:
	CPhysicDx9*		m_Physic;
	eDirectAttack	m_DirectAttack;
	Collision*		m_Collision;
public:
	bool isDead;
	DynamicObject(void);
	CPhysicDx9*			getPhysic() const { return m_Physic; }
	DynamicObject(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void UpdateBound();
	BOX GetBroadPhaseBox(D3DXVECTOR2);
	BOX GetBroadPhaseBox();
	BOX GetBoundForDynamicObject(D3DXVECTOR2);
	virtual void UpdateMovement() = 0;
	virtual ~DynamicObject(void);
};
#endif
