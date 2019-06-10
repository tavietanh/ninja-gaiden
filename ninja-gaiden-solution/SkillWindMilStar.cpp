#include "SkillWindMilStar.h"


SkillWindMilStar::SkillWindMilStar()
{

}
SkillWindMilStar::SkillWindMilStar(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) : Skill(_position, _direction, _objectID)
{
	this->m_Position.z = 1.0f;
}

void SkillWindMilStar::Initialize()
{
	this->m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SKILL_WINDMIL_STAR));
	this->m_Position.z = 1.0f;
	this->m_Physic->setVelocityX(1.0f);
	this->m_Physic->setAccelerate(D3DXVECTOR2(0.0f, 0.0f));
	this->m_TypeSkill = eIDTypeSkill::NINJA_WINDMIL_STAR;
	this->m_factor = 0.05;
	this->getPhysic()->setAccelerateX(-0.05f);
}

void SkillWindMilStar::UpdateMovement()
{
	Skill::UpdateMovement();
	D3DXVECTOR3 temp = m_Physic->getVelocity();
	float m_factory = m_factor / 10;
	int distancey = (CGlobal::Ninja_Y + 8) - ceil(this->m_Position.y);
	if (distancey>0)
	{
		this->getPhysic()->setAccelerateY(-m_factory);
	}
	else if (distancey<0)
		this->getPhysic()->setAccelerateY(m_factory);
	else if (distancey==0)
		this->getPhysic()->setAccelerateY(0);
	if (CGlobal::Ninja_X - ceil(this->m_Position.x)>0)
	{
		this->getPhysic()->setAccelerateX(-m_factor);
		if (temp.x < -3.0f) m_Physic->setVelocityX(-3.0f);
	}
	else {
		this->getPhysic()->setAccelerateX(m_factor);
		if (temp.x > 3.0f) m_Physic->setVelocityX(3.0f);
	}
}

SkillWindMilStar::~SkillWindMilStar()
{

}

