#include "Skill.h"


Skill::Skill()
{
	
}

Skill::Skill(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{

	this->m_Direction = _direction;
	this->m_eObjectID = _objectID;
	this->m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
}

void Skill::reset()
{
	this->m_factor = 0;
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
	case eObjectState::STATE_DEATH:
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
