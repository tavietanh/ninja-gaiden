#ifndef GIFTBUTERFLY_H
#define GIFTBUTERFLY_H

#include "DynamicObject.h"
#include "VirtualObject.h"
#include "CCamera.h"
#include "ItemManager.h"
#include "ThrowStar.h"
#include "WindmilStar.h"
#include "Flames.h"
#include "Freeze.h"
#include "Health.h"
#include "Point500.h"
#include "Point1000.h"
#include "FivePower.h"
#include "TenPower.h"
class GifButerfly : public DynamicObject
{
private:
	eObjectID m_IDItem;
	CSpriteDx9* sprite_alive;
	CSpriteDx9* sprite_dead;
public:
	GifButerfly();
	GifButerfly(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID, eObjectID idItem);
	void Initialize();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	bool CanCollisionWithVirtualObject(VirtualObject* virtualObject);
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~GifButerfly();
};

#endif
