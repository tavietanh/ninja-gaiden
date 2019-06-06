#ifndef __SWORD_ENEMY_THROW_H__
#define __SWORD_ENEMY_THROW_H__

#include "Skill.h"

class SwordEnemyThrow : public Skill
{
public:
	SwordEnemyThrow();
	SwordEnemyThrow(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateMovement();
	~SwordEnemyThrow();
};

#endif
