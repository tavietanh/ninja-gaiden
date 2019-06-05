#include "SkillPool.h"

SkillPool* SkillPool::m_Instance = 0;

SkillPool::SkillPool()
{

}

SkillPool* SkillPool::getInstance()
{
	if (SkillPool::m_Instance == 0)
	{
		SkillPool::m_Instance = new SkillPool();
	}

	return SkillPool::m_Instance;
}

void SkillPool::Initialize()
{
	std::queue<Skill*> queueThrowStar;
	for (int i = 0; i < 10; ++i)
	{
		SkillThrowStar* temp = new SkillThrowStar(D3DXVECTOR3(0.0f, 0.0f, 0.5f), eDirection::TOP, eObjectID::SKILL_NINJA);
		temp->Initialize();
		queueThrowStar.push(temp);
	}
	m_SkillPool.push_back(queueThrowStar);
	std::queue<Skill*> queueFlames;
	for (int i = 0; i < 50; ++i)
	{
		SkillFlames* temp = new SkillFlames(D3DXVECTOR3(0.0f, 0.0f, 0.5f), eDirection::TOP, eObjectID::SKILL_NINJA);
		temp->Initialize();
		queueFlames.push(temp);
	}
	m_SkillPool.push_back(queueFlames);
	std::queue<Skill*> queueWindmilStar;
	for (int i = 0; i < 10; ++i)
	{
		SkillWindMilStar* temp = new SkillWindMilStar(D3DXVECTOR3(0.0f, 0.0f, 0.5f), eDirection::TOP, eObjectID::SKILL_NINJA);
		temp->Initialize();
		queueWindmilStar.push(temp);
	}
	m_SkillPool.push_back(queueWindmilStar);
	std::queue<Skill*> queueSwordNinja;
	for (int i = 0; i < 10; ++i)
	{
		SwordNinja* temp = new SwordNinja(D3DXVECTOR3(0.0f, 0.0f, 0.5f), eDirection::TOP, eObjectID::SKILL_NINJA);
		temp->Initialize();
		queueSwordNinja.push(temp);
	}
	m_SkillPool.push_back(queueSwordNinja);
}

Skill* SkillPool::popSkillFromSkillPool(eIDTypeSkill _typeSkill, D3DXVECTOR3 _position, D3DXVECTOR2 _velocity, float _factor, float _rotationAngle)
{
	switch (_typeSkill)
	{
	case eIDTypeSkill::NINJA_THROW_STAR:
		if (m_SkillPool[eIDTypeSkill::NINJA_THROW_STAR].empty() == false)
		{
			SkillThrowStar* object = (SkillThrowStar*)m_SkillPool[eIDTypeSkill::NINJA_THROW_STAR].front();
			_position.z = 1.0f;
			object->setPosition(_position);
			object->setStartPosition(_position);
			object->getPhysic()->setVelocity(_velocity);
			object->setFactor(_factor);
			object->ResetLivingTime();
			m_SkillPool[eIDTypeSkill::NINJA_THROW_STAR].pop();

			return object;
		}
		break;
	case eIDTypeSkill::NINJA_FLAMES:
		if (m_SkillPool[eIDTypeSkill::NINJA_FLAMES].empty() == false)
		{
			SkillFlames* object = (SkillFlames*)m_SkillPool[eIDTypeSkill::NINJA_FLAMES].front();
			_position.z = 1.0f;
			object->setPosition(_position);
			object->setStartPosition(_position);
			object->getPhysic()->setVelocity(_velocity);
			object->setFactor(_factor);
			object->ResetLivingTime();
			m_SkillPool[eIDTypeSkill::NINJA_FLAMES].pop();

			return object;
		}
		break;
	case eIDTypeSkill::NINJA_WINDMIL_STAR:
		if (m_SkillPool[eIDTypeSkill::NINJA_WINDMIL_STAR].empty() == false)
		{
			SkillWindMilStar* object = (SkillWindMilStar*)m_SkillPool[eIDTypeSkill::NINJA_WINDMIL_STAR].front();
			_position.z = 1.0f;
			object->setPosition(_position);
			object->setStartPosition(_position);
			object->getPhysic()->setVelocity(_velocity);
			object->setFactor(_factor);
			object->ResetLivingTime();
			m_SkillPool[eIDTypeSkill::NINJA_WINDMIL_STAR].pop();

			return object;
		}
		break;
	case eIDTypeSkill::NINJA_SWORD:
		if (m_SkillPool[eIDTypeSkill::NINJA_SWORD].empty() == false)
		{
			SwordNinja* object = (SwordNinja*)m_SkillPool[eIDTypeSkill::NINJA_SWORD].front();
			_position.z = 0.0f;
			object->setPosition(_position);
			object->setStartPosition(_position);
			object->getPhysic()->setVelocity(_velocity);
			object->setFactor(_factor);
			object->ResetLivingTime();
			m_SkillPool[eIDTypeSkill::NINJA_SWORD].pop();

			return object;
		}
		break;
	default:
		return 0;
	}
	return 0;
}

void SkillPool::addSkillToSkillPool(Skill* _object)
{
	//if(_object->getID() == eObjectID::Skill_RAMBO)
	//{
	switch (_object->getTypeSkill())
	{
	case eIDTypeSkill::NINJA_THROW_STAR:
		_object->reset();
		m_SkillPool[eIDTypeSkill::NINJA_THROW_STAR].push((SkillThrowStar*)_object);
		break;
	case eIDTypeSkill::NINJA_FLAMES:
		_object->reset();
		m_SkillPool[eIDTypeSkill::NINJA_FLAMES].push((SkillFlames*)_object);
		break;
	case eIDTypeSkill::NINJA_WINDMIL_STAR:
		_object->reset();
		m_SkillPool[eIDTypeSkill::NINJA_WINDMIL_STAR].push((SkillWindMilStar*)_object);
		break;
	case eIDTypeSkill::NINJA_SWORD:
		_object->reset();
		m_SkillPool[eIDTypeSkill::NINJA_SWORD].push((SwordNinja*)_object);
		break;
	default:
		break;
	}
	//}
}

void SkillPool::releaseSkillPool()
{
	for (int i = 0; i < (int)m_SkillPool.size(); ++i)
	{
		while (m_SkillPool[i].empty() == false)
		{
			m_SkillPool[i].front()->Release();
			delete m_SkillPool[i].front();
			m_SkillPool[i].pop();
		}
	}

	m_SkillPool.clear();
	delete SkillPool::m_Instance;
	SkillPool::m_Instance = 0;
}

SkillPool::~SkillPool()
{

}
