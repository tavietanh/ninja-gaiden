#ifndef SWORD_NINJA_H
#define SWORD_NINJA_H

#include "Skill.h"
#include "CGlobal.h"

class SwordNinja : public Skill
{
public:
	SwordNinja();
	SwordNinja(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateMovement();
	~SwordNinja();
};

#endif