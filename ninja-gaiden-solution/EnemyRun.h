#ifndef ENEMYRUN_H
#define ENEMYRUN_H

#include "DynamicObject.h"
#include "VirtualObject.h"
#include "CCamera.h"

class EnemyRun : public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
	CSpriteDx9* sprite_dead;
	bool isJumb;
public:
	EnemyRun();
	EnemyRun(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	bool CanCollisionWithVirtualObject(VirtualObject* virtualObject);
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~EnemyRun();
};

#endif

