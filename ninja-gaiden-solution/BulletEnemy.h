#ifndef __SWORD_ENEMY_THROW_H__
#define __SWORD_ENEMY_THROW_H__

#include "Skill.h"

class BulletEnemy : public Skill
{
private:
	CSpriteDx9* sprite_rocket;
	CSpriteDx9* sprite_sword;
	CSpriteDx9* sprite_gun;
	CSpriteDx9* sprite_dead;
	CSpriteDx9* sprite_boss;
public:
	BulletEnemy();
	BulletEnemy(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateMovement();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateAnimation();
	~BulletEnemy();
};

#endif
