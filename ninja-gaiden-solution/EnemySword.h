#ifndef ENEMYSWORD_H
#define ENEMYSWORD_H

#include "DynamicObject.h"
#include "VirtualObject.h"
#include "CCamera.h"
#include "Skill.h"
class EnemySword : public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
	CSpriteDx9* sprite_dead;
	bool isJumb;
public:
	EnemySword();
	EnemySword(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	bool CanCollisionWithVirtualObject(VirtualObject* virtualObject);
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~EnemySword();
};

#endif

