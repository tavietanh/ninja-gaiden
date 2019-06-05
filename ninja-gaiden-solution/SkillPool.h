#ifndef __SKILLPOOL_H__
#define __SKILLPOOL_H__

#include "Skill.h"
#include "SkillThrowStar.h"
#include "SkillFlames.h"
#include "SkillWindMilStar.h"
#include "SwordNinja.h"
#include <vector>
#include <queue>

class SkillPool
{
private:
	std::vector<std::queue<Skill*>> m_SkillPool;
	static SkillPool* m_Instance;
	SkillPool();
	~SkillPool();
public:
	static SkillPool* getInstance();
	void Initialize();
	Skill* popSkillFromSkillPool(eIDTypeSkill, D3DXVECTOR3, D3DXVECTOR2, float, float _rotationAngle = 0.0f);
	void addSkillToSkillPool(Skill*);
	void releaseSkillPool();
};

#endif