#include "SkillFlames.h"


SkillFlames::SkillFlames()
{

}
SkillFlames::SkillFlames(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) : Skill(_position, _direction, _objectID)
{
	this->m_Position.z = 1.0f;
}

void SkillFlames::Initialize()
{
	this->m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SKILL_FLAMES));
	this->m_Position.z = 0.0f;
	this->m_Physic->setVelocityX(1.0f);
	this->m_Physic->setAccelerate(D3DXVECTOR2(0.0f, 0.0f));
	this->m_TypeSkill = eIDTypeSkill::NINJA_FLAMES;
	// because object class has a directattack
	// don't use directack
	this->m_DirectAttack = eDirectAttack::AD_TOP;
	this->m_factor = 0;
}

void SkillFlames::UpdateMovement()
{
	Skill::UpdateMovement();
	D3DXVECTOR3 tempPosition;

	if (this->m_factor == 100)
	{
		this->getPhysic()->setVelocityX(0.0f);
	}
	else if (this->m_factor == 0)
	{
		
	}
	else
	{
		tempPosition = D3DXVECTOR3(this->m_Position.x + this->getPhysic()->getVelocity().x - this->m_StartPosition.x, 0.0f, 0.0f);
		tempPosition.y = this->m_factor * tempPosition.x;
		this->getPhysic()->setVelocityY((tempPosition.y + this->m_StartPosition.y - this->m_Position.y));
	}
}

SkillFlames::~SkillFlames()
{

}

