#ifndef ENEMYEAGLE_H
#define ENEMYEAGLE_H

#include "DynamicObject.h"
#include "VirtualObject.h"
#include "CCamera.h"
#include "Skill.h"
class EnemyEagle : public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
	CSpriteDx9* sprite_dead;
	bool isJumb;
public:
	EnemyEagle();
	EnemyEagle(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~EnemyEagle();
};

#endif



