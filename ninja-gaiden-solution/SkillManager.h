#ifndef __SKILL_MANAGER_H__
#define __SKILL_MANAGER_H__

#include "Skill.h"
#include "SkillPool.h"
#include <list>

class SkillManager
{
private:
	//std::list<Skill* > m_ListSkillInGame;
	//LazerSkill* m_lazerShoot;
	SkillManager();
	~SkillManager();
public:
	std::list<Skill*> m_ListSkillInGame;
	static SkillManager* m_Instance;
	static SkillManager* getInstance();

	void Initialize();
	void addSkillIntoList(eIDTypeSkill, D3DXVECTOR3, D3DXVECTOR2, float _factor = 0.0f, float _rotationAngle = 0.0f);
	void popSkillFromList();
	void Update();
	void UpdateAnimation();
	void UpdateMovement();
	void UpdateCollision(CObjectDx9* checkingObject);
	void Render(SPRITEHANDLE spriteHandler);
	void Release();

	// Danh code
	list<Skill*> getListSkill() { return m_ListSkillInGame; }
	int GetAmountSkillOfType(eIDTypeSkill _type)
	{
		int result = 0;
		for (auto i = m_ListSkillInGame.begin(); i != m_ListSkillInGame.end(); ++i)
		{
			if ((*i)->getTypeSkill() == _type)
			{
				++result;
			}
		}
		return result;
	}
	void KillSkill(eIDTypeSkill _type)
	{
		for (auto i = m_ListSkillInGame.begin(); i != m_ListSkillInGame.end(); ++i)
		{
			if ((*i)->getTypeSkill() == _type)
			{
				(*i)->setObjectState(eObjectState::STATE_DEATH);
			}
		}
		//m_lazerShoot->setObjectState(eObjectState::STATE_DEATH);
	}
};

#endif