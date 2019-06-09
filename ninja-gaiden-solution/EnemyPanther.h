#ifndef ENEMYPANTHER_H
#define ENEMYPANTHER_H

#include "DynamicObject.h"
#include "VirtualObject.h"
#include "CCamera.h"
#include "Skill.h"
class EnemyPanther : public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
	CSpriteDx9* sprite_dead;
	bool isJumb;
public:
	EnemyPanther();
	EnemyPanther(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	bool CanCollisionWithVirtualObject(VirtualObject* virtualObject);
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~EnemyPanther();
};

#endif
