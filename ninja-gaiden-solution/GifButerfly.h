#ifndef GIFTBUTERFLY_H
#define GIFTBUTERFLY_H

#include "DynamicObject.h"
#include "VirtualObject.h"
#include "CCamera.h"
class GifButerfly : public DynamicObject
{
private:
	eObjectID m_IDItem;
	CSpriteDx9* sprite_main;
	CSpriteDx9* sprite_dead;
	bool isJumb;
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
