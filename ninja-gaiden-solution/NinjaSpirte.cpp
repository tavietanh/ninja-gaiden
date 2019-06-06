#include "NinjaSpirte.h"
#include "CInputDx9.h"


NinjaSpirte::NinjaSpirte(void)
{
	m_Run = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_NINJA_RUN));
	m_Jump= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_NINJA_JUMP));
	m_Idle = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_NINJA_IDLE));
	m_Hit = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_NINJA_HIT));
	m_Sit = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_NINJA_SIT));
	m_Sit_Hit = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_NINJA_SIT_HIT));
	m_Jump_Hit = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_NINJA_JUMP_HIT));
	m_Climb = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_NINJA_CLIMB));
	m_Skill = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_NINJA_SKILL));
	m_Ninja = m_Idle;
	m_isJump = false;
	m_previousState = (eObjectState)-1;
	resetInverseVariable();
}
void NinjaSpirte::resetInverseVariable()
{
	m_inversePositionY = -1;
}
void NinjaSpirte::UpdateAnimation(eObjectState _objectState)
{
	switch (_objectState)
	{
	case STATE_NINJA_IDLE:
	{
		if (m_previousState != _objectState)
		{
			m_Position = D3DXVECTOR3(0, 0, 0);
			m_frameSize = D3DXVECTOR2(17, 32);
			m_Ninja = m_Idle;

			resetInverseVariable();
		}
		this->Reset();
	}
	break;
	case STATE_NINJA_JUMP:
	{
		if (m_previousState != _objectState)
		{
			m_Position = D3DXVECTOR3(0, 0, 0);
			m_frameSize = D3DXVECTOR2(22, 22);
			m_Ninja = m_Jump;
			resetInverseVariable();
		}
		m_Ninja->UpdateAnimation(150);

	}
	break;
	case STATE_NINJA_DEAD:
	{
		if (m_previousState != _objectState)
		{
			m_Position = D3DXVECTOR3(0, 0, 0);
			m_frameSize = D3DXVECTOR2(22, 22);
			m_Ninja = m_Jump;
			resetInverseVariable();
		}
		m_Ninja->getAnimation()->setSourceRectAtIndex(0);
	}
	break;
	case STATE_NINJA_HIT:
	{
		if (m_previousState != _objectState)
		{
			m_Position = D3DXVECTOR3(11, 0, 0);
			m_frameSize = D3DXVECTOR2(17, 31);
			m_Ninja = m_Hit;
			resetInverseVariable();
		}
		m_Ninja->UpdateAnimation(200);
	}
	break;
	case STATE_NINJA_RUN:
	{
		if (m_previousState != _objectState)
		{
			m_Position = D3DXVECTOR3(0, 0, 0);
			m_frameSize = D3DXVECTOR2(22, 31);
			m_Ninja = m_Run;
			resetInverseVariable();
		}
		m_Ninja->UpdateAnimation(200);
	}
	break;
	case STATE_NINJA_SIT:
	{
		if (m_previousState != _objectState)
		{
			m_Position = D3DXVECTOR3(0, 0, 0);
			m_frameSize = D3DXVECTOR2(17, 25);
			m_Ninja = m_Sit;
			resetInverseVariable();
		}
		this->Reset();
	}
	break;
	case STATE_NINJA_SIT_HIT:
	{
		if (m_previousState != _objectState)
		{
			m_Position = D3DXVECTOR3(11, 0, 0);
			m_frameSize = D3DXVECTOR2(39, 23);
			m_Ninja = m_Sit_Hit;
			resetInverseVariable();
		}
		m_Ninja->UpdateAnimation(200);
	}
	break;
	case STATE_NINJA_JUMP_HIT:
	{
		if (m_previousState != _objectState)
		{
			m_Position = D3DXVECTOR3(0, 0, 0);
			m_frameSize = D3DXVECTOR2(25, 26);
			m_Ninja = m_Jump_Hit;
			resetInverseVariable();
		}
		m_Ninja->UpdateAnimation(200);
	}
	break;
	case STATE_NINJA_HANG:
	{
		if (m_previousState != _objectState)
		{
			m_Position = D3DXVECTOR3(0, 0, 0);
			m_frameSize = D3DXVECTOR2(16, 31);
			m_Ninja = m_Climb;
			resetInverseVariable();
		}
		m_Ninja->getAnimation()->setSourceRectAtIndex(0);
	}
	break;
	case STATE_NINJA_CLIMB:
	{
		if (m_previousState != _objectState)
		{
			m_Position = D3DXVECTOR3(0, 0, 0);
			m_frameSize = D3DXVECTOR2(16, 31);
			m_Ninja = m_Climb;
			resetInverseVariable();
		}
		m_Ninja->UpdateAnimation(200);
	}
	break;
	case STATE_NINJA_SKILL:
	{
		if (m_previousState != _objectState)
		{
			m_Position = D3DXVECTOR3(4, 0, 0);
			m_frameSize = D3DXVECTOR2(26, 31);
			m_Ninja = m_Skill;
			resetInverseVariable();
		}
		m_Ninja->UpdateAnimation(200);
	}
	break;
	default:
		break;
	}
}
void NinjaSpirte::Reset()
{
	m_Ninja->getAnimation()->Reset();

}
void NinjaSpirte::Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ESpriteEffect effect, float rotateAngle, float scale, float deep, D3DXCOLOR color)
{
	if(effect == ESpriteEffect::None)
		m_Ninja->Render(spriteHandle, D3DXVECTOR2(position.x+m_Position.x, position.y+m_Position.y), effect, rotateAngle, scale, deep, color);
	if(effect == ESpriteEffect::Horizontally)
		m_Ninja->Render(spriteHandle, D3DXVECTOR2(position.x - m_Position.x, position.y + m_Position.y), effect, rotateAngle, scale, deep, color);

}

NinjaSpirte::~NinjaSpirte()
{
}
