#ifndef __SKILL_THROW_STAR_H__
#define __SKILL_THROW_STAR_H__

#include "Skill.h"

class SkillThrowStar : public Skill
{
public:
	SkillThrowStar();
	SkillThrowStar(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateMovement();
	~SkillThrowStar();
};

#endif
