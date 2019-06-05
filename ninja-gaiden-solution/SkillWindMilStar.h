#ifndef __SKILL_WINDMIL_STAR_H__
#define __SKILL_WINDMIL_STAR_H__

#include "Skill.h"
#include "CGlobal.h"

class SkillWindMilStar : public Skill
{
public:
	SkillWindMilStar();
	SkillWindMilStar(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateMovement();
	~SkillWindMilStar();
};

#endif