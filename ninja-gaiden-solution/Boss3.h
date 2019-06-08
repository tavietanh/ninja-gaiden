#ifndef BOSS3_H
#define BOSS3_H

#include "DynamicObject.h"
#include "VirtualObject.h"
#include "CCamera.h"
#include "SkillManager.h"
class Boss3 : public DynamicObject
{
private:
	CSpriteDx9* sprite_jump;
	CSpriteDx9* sprite_dead;
	float turnjump;
	int countBullet;
	bool isJump;
	int healthBoss;
public:
	Boss3();
	Boss3(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	D3DXVECTOR3 GetStartPositionOfSkill(float x, float y);
	int getHealthBoss() { return healthBoss; };
	void Initialize();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	bool CanCollisionWithVirtualObject(VirtualObject* virtualObject);
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~Boss3();
};

#endif
