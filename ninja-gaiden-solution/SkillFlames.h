#ifndef __SKILL_FlAMES_H__
#define __SKILL_FlAMES_H__

#include "Skill.h"

class SkillFlames : public Skill
{
public:
	SkillFlames();
	SkillFlames(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateMovement();
	~SkillFlames();
};

#endif
