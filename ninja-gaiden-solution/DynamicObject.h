#ifndef DYNAMIC_OBJECT
#define DYNAMIC_OBJECT

#include "CObjectDx9.h"
#include "CGameTimeDx9.h"
#include "EDirection.h"

class DynamicObject : public CObjectDx9
{
public:
	DynamicObject();
	void UpdateBound();
	DynamicObject(D3DXVECTOR3 _position, eDirection _direction);
	~DynamicObject();
};
#endif
