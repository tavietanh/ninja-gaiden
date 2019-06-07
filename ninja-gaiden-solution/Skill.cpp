#include "Skill.h"


Skill::Skill()
{
	
}

Skill::Skill(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	this->sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOSION));
	this->m_Direction = _direction;
	this->m_eObjectID = _objectID;
	this->m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
}

void Skill::reset()
{
	this->getPhysic()->setVelocityX(2.0f);
	this->getPhysic()->setVelocityY(0.0f);
}

void Skill::ResetLivingTime()
{
	this->m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
	m_livingTime = 0;
}

void Skill::Release()
{
	this->m_Sprite = 0;
}

void Skill::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite != 0)
	{
		m_Sprite->Render(spriteHandle, this->getPositionVec2(), this->m_Sprite->getSpriteEffect(), this->m_Sprite->getRotate(),
			this->m_Sprite->getScale(), this->getPositionVec3().z);
	}
}

void Skill::Update()
{
	m_livingTime += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	if (this->getTypeSkill() == eIDTypeSkill::NINJA_SWORD && m_livingTime>400)
	{
		m_ObjectState = eObjectState::STATE_DEATH;
		reset();
	}
	if (!Intersect(Camera::getInstance()->getBound(), this->getBound()))
	{
		m_ObjectState = eObjectState::STATE_DEATH;
		reset();
	}
}

void Skill::UpdateAnimation()
{
	this->m_Sprite->UpdateAnimation(200);
	switch (this->m_ObjectState)
	{
	case eObjectState::STATE_ALIVE_MOVE:
		this->m_Sprite->UpdateAnimation(200);
		break;
	case eObjectState::STATE_BEFORE_DEATH:
		this->m_Sprite = sprite_dead;
		m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_TimeChangeState > 200)
		{
			m_Sprite->setScale(m_Sprite->getScale()*1.5f);
		}
		if (m_TimeChangeState > 215)
		{
			m_ObjectState = eObjectState::STATE_DEATH;
			m_TimeChangeState = 0;
		}
		break;
	case eObjectState::STATE_DEATH:
		this->m_Sprite = 0;
		break;
	default:
		break;
	}
}

void Skill::UpdateCollision(CObjectDx9* checkingObject)
{

}

void Skill::UpdateMovement()
{
	this->m_Physic->UpdateMovement(&this->m_Position);
}

Skill::~Skill()
{

}
