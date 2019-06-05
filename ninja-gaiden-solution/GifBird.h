#ifndef GIFTBIRD_H
#define GIFTBIRD_H

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
class GifBird : public DynamicObject
{
private:
	eObjectID	m_IDItem;
	CSpriteDx9*	sprite_dead;
	CSpriteDx9*	sprite_alive;
public:
	GifBird();
	GifBird(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID, eObjectID _idItem);
	void Initialize();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~GifBird();
};

#endif
