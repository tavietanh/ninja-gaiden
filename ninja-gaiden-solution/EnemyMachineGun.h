#ifndef ENEMY_MACHINE_GUN_H
#define ENEMY_MACHINE_GUN_H

#include "DynamicObject.h"
#include "VirtualObject.h"
#include "CCamera.h"
#include "SkillManager.h"
class EnemyMachineGun : public DynamicObject
{
private:
	CSpriteDx9* sprite_shoot;
	CSpriteDx9* sprite_alivemove;
	CSpriteDx9* sprite_dead;
	int _distance_X;
	int _distance_Y;
	bool isShoot;
	int countBullet;
	D3DXVECTOR2 preVelocity;
public:
	D3DXVECTOR3 GetStartPositionOfSkill(float x, float y);
	EnemyMachineGun();
	EnemyMachineGun(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~EnemyMachineGun();
};

#endif
