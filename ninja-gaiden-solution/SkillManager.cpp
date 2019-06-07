#include "SkillManager.h"

SkillManager* SkillManager::m_Instance = 0;

SkillManager::SkillManager()
{

}

void SkillManager::Initialize()
{
	SkillPool::getInstance()->Initialize();
}

void SkillManager::addSkillIntoList(eIDTypeSkill typeSkill, D3DXVECTOR3 position, D3DXVECTOR2 _velocity, float _factor, float _rotationAngle)
{
	if (typeSkill == eIDTypeSkill::NINJA_THROW_STAR)
	{
		this->m_ListSkillInGame.push_back((SkillThrowStar*)SkillPool::getInstance()->popSkillFromSkillPool(typeSkill, position, _velocity, _factor));
	}
	if (typeSkill == eIDTypeSkill::NINJA_FLAMES)
	{
		this->m_ListSkillInGame.push_back((SkillFlames*)SkillPool::getInstance()->popSkillFromSkillPool(typeSkill, position, _velocity, _factor));
	}
	if (typeSkill == eIDTypeSkill::NINJA_WINDMIL_STAR)
	{
		this->m_ListSkillInGame.push_back((SkillWindMilStar*)SkillPool::getInstance()->popSkillFromSkillPool(typeSkill, position, _velocity, _factor));
	}
	if (typeSkill == eIDTypeSkill::NINJA_SWORD)
	{
		this->m_ListSkillInGame.push_back((SwordNinja*)SkillPool::getInstance()->popSkillFromSkillPool(typeSkill, position, _velocity, _factor));
	}
	if (typeSkill == eIDTypeSkill::ENEMY_BULLET)
	{
		this->m_ListSkillInGame.push_back((BulletEnemy*)SkillPool::getInstance()->popSkillFromSkillPool(typeSkill, position, _velocity, _factor));
	}
}

void SkillManager::popSkillFromList()
{
	for (std::list<Skill*>::iterator i = this->m_ListSkillInGame.begin(); i != this->m_ListSkillInGame.end(); )
	{
		if ((*i)->getObjectState() == eObjectState::STATE_DEATH)
		{
			SkillPool::getInstance()->addSkillToSkillPool((*i));
			//this->m_ListSkillInGame.remove((*i));
			i = this->m_ListSkillInGame.erase(i);
		}
		else
		{
			++i;
		}
	}
}

SkillManager* SkillManager::getInstance()
{
	if (SkillManager::m_Instance == 0)
	{
		SkillManager::m_Instance = new SkillManager();
	}

	return SkillManager::m_Instance;
}

void SkillManager::Update()
{
	for (std::list<Skill*>::iterator i = this->m_ListSkillInGame.begin(); i != this->m_ListSkillInGame.end(); ++i)
	{
		(*i)->Update();
	}
	popSkillFromList();
}

void SkillManager::UpdateAnimation()
{
	for (std::list<Skill*>::iterator i = this->m_ListSkillInGame.begin(); i != this->m_ListSkillInGame.end(); ++i)
	{
		(*i)->UpdateAnimation();
	}
}

void SkillManager::UpdateMovement()
{
	for (std::list<Skill*>::iterator i = this->m_ListSkillInGame.begin(); i != this->m_ListSkillInGame.end(); ++i)
	{
		(*i)->UpdateMovement();
	}
}

void SkillManager::UpdateCollision(CObjectDx9* checkingObject)
{
	for (std::list<Skill*>::iterator i = this->m_ListSkillInGame.begin(); i != this->m_ListSkillInGame.end(); ++i)
	{
		(*i)->UpdateCollision(checkingObject);
	}
}

void SkillManager::Render(SPRITEHANDLE spriteHandler)
{
	for (std::list<Skill*>::iterator i = this->m_ListSkillInGame.begin(); i != this->m_ListSkillInGame.end(); ++i)
	{
		(*i)->Render(spriteHandler);
	}
}

void SkillManager::Release()
{
	for (std::list<Skill*>::iterator i = this->m_ListSkillInGame.begin(); i != this->m_ListSkillInGame.end(); ++i)
	{
		(*i)->Release();
		delete (*i);
	}
	SkillPool::getInstance()->releaseSkillPool();
	this->m_ListSkillInGame.clear();
	delete SkillManager::m_Instance;
	SkillManager::m_Instance = 0;
}

SkillManager::~SkillManager()
{

}
