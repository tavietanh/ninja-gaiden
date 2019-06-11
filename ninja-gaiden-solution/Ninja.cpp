#include "Ninja.h"

#define VELOCITY_Y_JUMP				3.3f
#define VELOCITY_X_MOVE_TO_RIGHT	1.1f
#define VELOCITY_Y_MOVE_TO_LEFT		-1.1f

Ninja::Ninja()
{
}
void Ninja::Initialize()
{

}
RECT Ninja::getBound()
{
	RECT tempBound = RECT();

	tempBound.left = (long)(m_Position.x - m_NinjaSprite->GetFrameSize().x / 2);
	tempBound.right = (long)(tempBound.left + m_NinjaSprite->GetFrameSize().x);
	tempBound.top = (long)(m_Position.y + m_NinjaSprite->GetFrameSize().y / 2);
	tempBound.bottom = (long)(tempBound.top - m_NinjaSprite->GetFrameSize().y);

	return tempBound;
}
Ninja::Ninja(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	m_ObjectState = eObjectState::STATE_NINJA_JUMP;
	m_NinjaSprite = new NinjaSpirte();
	isJump = false;
	isSetVelocityDeathState = false;
	isFall = false;
	isClimb = false;
	this->m_Physic->setAccelerate(D3DXVECTOR2(0.0f, -0.1f));
	m_Position.z = 1.0f;
	m_timeInvulnerable = 0;
	m_colorAlpha = 255;
	m_inverseColorAlpha = 1;
	isInvulnerable = true;
	prePosX = 0;
	finalPosX = 0;
	setSkillNinja(eIDItem::SKILL_WINDMIL_STAR);
}

int Ninja::CheckOutBottomCamera()
{
	if (m_Position.y < Camera::getInstance()->getBound().bottom)
	{
		if (m_ObjectState != eObjectState::STATE_NINJA_DEAD)
		{
			CGlobal::healthNinja = 0;
			m_ObjectState = eObjectState::STATE_NINJA_DEAD;
			
		}
		isFall = false;
		m_timeBeforeDeadBottom += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_timeBeforeDeadBottom > 3000)
		{
			m_timeBeforeDeadBottom = 0;
			m_ObjectState = eObjectState::STATE_NINJA_DEAD;
			m_timeDeath = 3000;
		}
	}
	return 0;
}

void Ninja::UpdateAnimation()
{
	m_NinjaSprite->UpdateAnimation(m_ObjectState);
	if (isInvulnerable)
	{
		UpdateInvulnerableAnimation();
	}
}
int Ninja::UpdateInvulnerableAnimation()
{
	m_colorAlpha -= 2 * m_inverseColorAlpha;
	if (m_colorAlpha < 100 + 2 || m_colorAlpha > 255 - 2)
	{
		m_inverseColorAlpha *= -1;
		m_timeInvulnerable++;
	}
	if (m_colorAlpha < 100)
	{
		m_colorAlpha = 100;
	}
	if (m_colorAlpha > 255)
	{
		m_colorAlpha = 255;
	}
	if (m_timeInvulnerable > 0.5 && m_colorAlpha == 255)
	{
		m_timeInvulnerable = 0;
		isInvulnerable = false;
		isSetVelocityDeathState = false;
	}
	return 0;
}
void Ninja::UpdateMovement()
{
	if (Camera::getInstance()->getBound().left > this->m_Position.x - m_NinjaSprite->GetFrameSize().x / 2)
	{
		m_Position.x = Camera::getInstance()->getBound().left + 1 + m_NinjaSprite->GetFrameSize().x / 2;
		m_Physic->setVelocityX(0.0f);
	}

	if (Camera::getInstance()->getBound().right < this->m_Position.x + m_NinjaSprite->GetFrameSize().x / 2)
	{
		m_Position.x = Camera::getInstance()->getBound().right - 1 - m_NinjaSprite->GetFrameSize().x / 2;
		m_Physic->setVelocityX(0.0f);
	}

	this->m_Physic->UpdateMovement(&m_Position);

	if (m_ObjectState == STATE_NINJA_JUMP || m_ObjectState == STATE_NINJA_DEAD)
	{
		if (m_maxPositionY < m_Position.y)
		{
			m_maxPositionY = m_Position.y;
		}
	}
	CGlobal::Ninja_X = (int)(getPositionVec2().x);
	CGlobal::Ninja_Y = (int)(getPositionVec2().y);
}void Ninja::Hit()
{
	if (SkillManager::getInstance()->GetAmountSkillOfType(eIDTypeSkill::NINJA_SWORD) < 1)
	{
		SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_NINJA_HIT)->Play();
		if (m_Direction == eDirection::LEFT)
		{
			SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::NINJA_SWORD, GetStartPositionOfSkill(-18, 4), D3DXVECTOR2(0.0f, 0.0f), 0);
		}
		if (m_Direction == eDirection::RIGHT)
		{
			SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::NINJA_SWORD, GetStartPositionOfSkill(18, 4), D3DXVECTOR2(0.0f, 0.0f), 0);
		}
	}
}
void Ninja::SitHit()
{
	if (SkillManager::getInstance()->GetAmountSkillOfType(eIDTypeSkill::NINJA_SWORD) < 1)
	{
		SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_NINJA_HIT)->Play();
		if (m_Direction == eDirection::LEFT)
		{
			SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::NINJA_SWORD, GetStartPositionOfSkill(-14, 6), D3DXVECTOR2(0.0f, 0.0f), 0);
		}
		if (m_Direction == eDirection::RIGHT)
		{
			SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::NINJA_SWORD, GetStartPositionOfSkill(14, 6), D3DXVECTOR2(0.0f, 0.0f), 0);
		}
	}
}
void Ninja::HandleInput()
{
	CheckOutBottomCamera();
	switch (m_ObjectState)
	{
		case STATE_NINJA_IDLE:
		{
			HandleInputIdleState();
		}
		break;
		case STATE_NINJA_JUMP:
		{
			HandleInputJumpState();
		}
		break;
		case STATE_NINJA_HIT:
		{
			HandleInputHitState();
		}
		break;
		case STATE_NINJA_SKILL:
		{
			HandleInputSkillState();
		}
		break;
		case STATE_NINJA_RUN:
		{
			HandleInputRunState();
		}
		break;
		case STATE_NINJA_SIT:
		{
			HandleInputSitState();
		}
		break;
		case STATE_NINJA_SIT_HIT:
		{
			HandleInputSitHitState();
		}
		break;
		case STATE_NINJA_DEAD:
		{
			HandleInputDeadState();
		}
		break;
		case STATE_NINJA_HANG:
		{
			HandleInputHangState();
		}
		break;
		case STATE_NINJA_CLIMB:
		{
			HandleInputClimbState();
		}
		break;
		default:
			break;
	}
	if (isFall)
	{
		m_ObjectState = eObjectState::STATE_NINJA_FALL;
	}
	if (m_ObjectState != eObjectState::STATE_NINJA_HIT 
		&& m_ObjectState != eObjectState::STATE_NINJA_SIT_HIT 
		&& m_ObjectState != eObjectState::STATE_NINJA_SKILL)
	{
		m_timeHit = 0;
	}
}
int Ninja::HandleInputDeadState()
{
	if (!isSetVelocityDeathState)
	{
		m_Physic->setVelocityY(2.0f);
		if (m_Direction == eDirection::RIGHT)
		{
			m_Physic->setVelocityX(-0.5f);
		}
		if (m_Direction == eDirection::LEFT)
		{
			m_Physic->setVelocityX(0.5f);
		}
		isSetVelocityDeathState = true;
		isInvulnerable = true;
	}
	m_timeDeath += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	//if (m_timeDeath > 2000)
	//{
	//	m_timeDeath = 0;
	//	isSetVelocityDeathState = false;
	//	m_ObjectState = eObjectState::STATE_NINJA_JUMP;
	//	m_Position.x = (float)(Camera::getInstance()->getBound().left + 128);
	//	m_Position.y = (float)(Camera::getInstance()->getBound().top - 32);
	//	this->m_Physic->setAccelerate(D3DXVECTOR2(0.0f, -0.1f));
	//	m_Physic->setVelocityX(0.0f);
	//	m_Physic->setVelocityY(0.0f);
	//	isInvulnerable = true;
	//}
	return 0;
}
int Ninja::HandleInputSkillState()
{
	if (isJump == true)
	{
		if (CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown())
		{
			if (m_Direction == eDirection::LEFT)
				m_Physic->setVelocityX(VELOCITY_X_MOVE_TO_RIGHT - 0.5f);
			else m_Physic->setVelocityX(VELOCITY_X_MOVE_TO_RIGHT);
			m_Physic->setVelocityX(VELOCITY_X_MOVE_TO_RIGHT);
		}
		if (CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
		{
			if (m_Direction == eDirection::LEFT)
				m_Physic->setVelocityX(VELOCITY_Y_MOVE_TO_LEFT);
			else m_Physic->setVelocityX(VELOCITY_Y_MOVE_TO_LEFT + 0.5f);
		}
	}
	m_timeHit += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	if (m_timeHit > 600)
	{
		m_ObjectState = eObjectState::STATE_NINJA_IDLE;
	}
	return 0;
}
int Ninja::HandleInputHangState() 
{
	if (m_Direction == eDirection::LEFT)
	{
		if (CInputDx9::getInstance()->IsKeyRightDownAndKeyXDown())
		{
			SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_NINJA_JUMP)->Play();
			m_ObjectState = eObjectState::STATE_NINJA_JUMP;
			m_Physic->setVelocityY(VELOCITY_Y_JUMP);
			return 0;
		}
	}
	if (m_Direction == eDirection::RIGHT)
	{
		if (CInputDx9::getInstance()->IsKeyLeftDownAndKeyXDown())
		{
			SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_NINJA_JUMP)->Play();
			m_ObjectState = eObjectState::STATE_NINJA_JUMP;
			m_Physic->setVelocityY(VELOCITY_Y_JUMP);
			m_Physic->setVelocityX(-0.6f);
			return 0;
		}
	}
	if (isClimb)
	{
		if (CInputDx9::getInstance()->IsKeyUpDownAndKeyDownUp() || CInputDx9::getInstance()->IsKeyUpUpAndKeyDownDown())
		{
			m_ObjectState = eObjectState::STATE_NINJA_CLIMB;
			return 0;
		}
	}
}
int Ninja::HandleInputSitState()
{
	if (!CInputDx9::getInstance()->IsKeyDown(DIK_DOWN) || CInputDx9::getInstance()->IsKeyUpDownAndKeyDownDown())
	{
		m_ObjectState = eObjectState::STATE_NINJA_IDLE;
		return 0;
	}
	if(CInputDx9::getInstance()->IsKeyDown(DIK_Z)&& CInputDx9::getInstance()->IsKeyDown(DIK_DOWN))
	{
		SitHit();
		m_ObjectState = eObjectState::STATE_NINJA_SIT_HIT;
	}
	return 0;
}
int Ninja::HandleInputSitHitState()
{
	m_timeHit += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	if (m_timeHit > 600)
	{
		m_ObjectState = eObjectState::STATE_NINJA_SIT;
	}
	return 0;
}
int Ninja::HandleInputIdleState()
{
	m_Physic->setVelocityX(0.0f);
	if (CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown() || CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
	{
		m_ObjectState = eObjectState::STATE_NINJA_RUN;
		return 0;
	}
	if (CInputDx9::getInstance()->IsKeyUpUpAndKeyDownDown())
	{
		m_ObjectState = eObjectState::STATE_NINJA_SIT;
		return 0;
	}
	if (CInputDx9::getInstance()->IsKeyDown(DIK_X))
	{
		SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_NINJA_JUMP)->Play();
		m_ObjectState = eObjectState::STATE_NINJA_JUMP;
		m_Physic->setVelocityY(VELOCITY_Y_JUMP);
		return 0;
	}
	if (CInputDx9::getInstance()->IsKeyUpUpAndKeyZDown())
	{
		Hit();
		m_ObjectState = eObjectState::STATE_NINJA_HIT;
		return 0;
	}
	if (CInputDx9::getInstance()->IsKeyUpDownAndKeyZDown())
	{
		UseSkill();
		m_ObjectState = eObjectState::STATE_NINJA_SKILL;
	}
	return 1;
}
int Ninja::HandleInputJumpState()
{
	isJump = true;
	if (CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown())
	{
		if(m_Direction == eDirection::LEFT)
			m_Physic->setVelocityX(VELOCITY_X_MOVE_TO_RIGHT- 0.5f);
		else m_Physic->setVelocityX(VELOCITY_X_MOVE_TO_RIGHT);
	}
	if (CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
	{
		if (m_Direction == eDirection::LEFT)
			m_Physic->setVelocityX(VELOCITY_Y_MOVE_TO_LEFT);
		else m_Physic->setVelocityX(VELOCITY_Y_MOVE_TO_LEFT+0.5f);
	}
	if (CInputDx9::getInstance()->IsKeyUpDownAndKeyDownUp())
	{
		
	}
	if (CInputDx9::getInstance()->IsKeyUpUpAndKeyDownDown())
	{
		
	}
	if (CInputDx9::getInstance()->IsKeyUpUpAndKeyZDown())
	{
		Hit();
		m_ObjectState = eObjectState::STATE_NINJA_HIT;
		return 0;
	}
	if (CInputDx9::getInstance()->IsKeyUpDownAndKeyZDown())
	{
		m_ObjectState = eObjectState::STATE_NINJA_SKILL;
		UseSkill();
		return 0;
	}
	return 0;
}
int Ninja::HandleInputHitState()
{
	if (isJump == true)
	{
		if (CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown())
		{
			if (m_Direction == eDirection::LEFT)
				m_Physic->setVelocityX(VELOCITY_X_MOVE_TO_RIGHT - 0.5f);
			else m_Physic->setVelocityX(VELOCITY_X_MOVE_TO_RIGHT);
			m_Physic->setVelocityX(VELOCITY_X_MOVE_TO_RIGHT);
		}
		if (CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
		{
			if (m_Direction == eDirection::LEFT)
				m_Physic->setVelocityX(VELOCITY_Y_MOVE_TO_LEFT);
			else m_Physic->setVelocityX(VELOCITY_Y_MOVE_TO_LEFT + 0.5f);
		}
	}
	m_timeHit += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();

	if (m_timeHit > 600)
	{
		m_ObjectState = eObjectState::STATE_NINJA_IDLE;
	}
	return 0;
}
int Ninja::HandleInputRunState()
{
	if (CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightDown())
	{
		m_Physic->setVelocityX(VELOCITY_X_MOVE_TO_RIGHT);
		m_Direction = eDirection::RIGHT;
	}
	if (CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightUp())
	{
		m_Physic->setVelocityX(VELOCITY_Y_MOVE_TO_LEFT);
		m_Direction = eDirection::LEFT;
	}
	if (CInputDx9::getInstance()->IsKeyLeftUpAndKeyRightUp() || CInputDx9::getInstance()->IsKeyLeftDownAndKeyRightDown())
	{
		m_ObjectState = eObjectState::STATE_NINJA_IDLE;
	}
	if (CInputDx9::getInstance()->IsKeyUpUpAndKeyZDown())
	{
		Hit();
		m_ObjectState = eObjectState::STATE_NINJA_HIT;
		return 0;
	}
	if (CInputDx9::getInstance()->IsKeyDown(DIK_X))
	{
		SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_NINJA_JUMP)->Play();
		m_ObjectState = eObjectState::STATE_NINJA_JUMP;
		m_Physic->setVelocityY(VELOCITY_Y_JUMP);

		return 0;
	}
	return 0;
}
int Ninja::HandleInputClimbState()
{
	if (CInputDx9::getInstance()->IsKeyUpDownAndKeyDownUp())
	{
		m_Physic->setVelocityY(VELOCITY_X_MOVE_TO_RIGHT/2);
		if (m_Position.y >= maxClimb)
		{
			m_Position.y = maxClimb;
			m_Physic->setVelocityY(0.0f);
		}
	}
	if (CInputDx9::getInstance()->IsKeyUpUpAndKeyDownDown())
	{
		m_Physic->setVelocityY(VELOCITY_Y_MOVE_TO_LEFT/2);
		if (m_Position.y <= minClimb)
		{
			m_Position.y = minClimb;
			m_Physic->setVelocityY(0.0f);
		}
	}
	if (CInputDx9::getInstance()->IsKeyUpUpAndKeyDownUp() || CInputDx9::getInstance()->IsKeyUpDownAndKeyDownDown())
	{
		m_ObjectState = eObjectState::STATE_NINJA_HANG;
	}
	return 0;
}
void Ninja::UseSkill()
{
	switch (m_SkillNinja)
	{
	case SKILL_SWORD:
		break;
	case SKILL_FLAMES:
		if (CGlobal::skills >= 5)
		{
			for (int i = 0; i < 3; i++)
			{
				CGlobal::skills -= 5;
				SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_FLAMES)->Play();
				if (m_Direction == eDirection::LEFT)
				{
					SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::NINJA_FLAMES, GetStartPositionOfSkill(-10, 0), D3DXVECTOR2(-1.0f, 2.0f*float(10 + i * 2) / 10), 0);
				}
				if (m_Direction == eDirection::RIGHT)
				{
					SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::NINJA_FLAMES, GetStartPositionOfSkill(10, 0), D3DXVECTOR2(1.0f, 2.0f*float(10 + i * 2) / 10), 0);
				}
				if (m_Direction == eDirection::LEFT)
				{
					SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::NINJA_FLAMES, GetStartPositionOfSkill(-18, -4), D3DXVECTOR2(-1.0f, 2.0f*float(10 + i * 2) / 10), 0);
				}
				if (m_Direction == eDirection::RIGHT)
				{
					SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::NINJA_FLAMES, GetStartPositionOfSkill(18, -4), D3DXVECTOR2(1.0f, 2.0f*float(10 + i * 2) / 10), 0);
				}
				if (m_Direction == eDirection::LEFT)
				{
					SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::NINJA_FLAMES, GetStartPositionOfSkill(-18, 4), D3DXVECTOR2(-1.0f, 2.0f*float(10 + i * 2) / 10), 0);
				}
				if (m_Direction == eDirection::RIGHT)
				{
					SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::NINJA_FLAMES, GetStartPositionOfSkill(18, 4), D3DXVECTOR2(1.0f, 2.0f*float(10 + i * 2) / 10), 0);
				}
			}
		}
		break;
	case SKILL_THROW_STAR:
		if (CGlobal::skills >= 3)
		{
			CGlobal::skills -= 3;
			SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_THROW_STAR)->Play();
			if (m_Direction == eDirection::LEFT)
			{
				SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::NINJA_THROW_STAR, GetStartPositionOfSkill(-14, 8), D3DXVECTOR2(-3.0f, 0.0f), 0);
			}
			if (m_Direction == eDirection::RIGHT)
			{
				SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::NINJA_THROW_STAR, GetStartPositionOfSkill(14, 8), D3DXVECTOR2(3.0f, 0.0f), 0);
			}
		}
		break;
	case SKILL_JUMP_HIT:
		break;
	case SKILL_WINDMIL_STAR:
		if (CGlobal::skills >= 5)
		{
			CGlobal::skills -= 5;
			if (SkillManager::getInstance()->GetAmountSkillOfType(eIDTypeSkill::NINJA_WINDMIL_STAR) < 1)
			{
				SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_WINDMIL_STAR)->Play();
				if (m_Direction == eDirection::LEFT)
				{
					SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::NINJA_WINDMIL_STAR, GetStartPositionOfSkill(-14, 8), D3DXVECTOR2(-2.5f, 0.0f), -0.05f);
				}
				if (m_Direction == eDirection::RIGHT)
				{
					SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::NINJA_WINDMIL_STAR, GetStartPositionOfSkill(14, 8), D3DXVECTOR2(2.5f, 0.0f), -0.05f);
				}
			}
		}
		break;
	default:
		break;
	}
}
D3DXVECTOR3 Ninja::GetStartPositionOfSkill(float x, float y)
{
	return D3DXVECTOR3(m_Position.x + x, m_Position.y + y, 0);
}
int Ninja::UpdateCollisionTileBase(IDDirection collideDirection, CObjectDx9* checkingObject)
{
	if (collideDirection == IDDirection::DIR_TOP && checkingObject != m_ignoreCollisionObject)
	{
		isFall = false;

		if (m_ObjectState == STATE_NINJA_JUMP || m_ObjectState == STATE_NINJA_DEAD)
		{
			if (m_Physic->getVelocity().y < 0)
			{
				if (m_ObjectState == STATE_NINJA_JUMP && m_maxPositionY - checkingObject->getPositionVec2().y > 37)
				{
					isJump = false;
					m_ObjectState = STATE_NINJA_IDLE;
					this->m_Position.y += this->m_Collision->m_MoveY;
					m_Physic->setVelocityY(0.0f);
					m_maxPositionY = 0;
				}
				if (m_ObjectState == STATE_NINJA_DEAD && m_maxPositionY - checkingObject->getPositionVec2().y > 37)
				{
					m_ObjectState = STATE_NINJA_IDLE;
					this->m_Position.y += this->m_Collision->m_MoveY;
					m_Physic->setVelocityY(0.0f);
					m_maxPositionY = 0;
				}
				return 0;
			}
		}
		else
		{
			if (m_ObjectState == STATE_NINJA_FALL)
			{
				m_ObjectState = STATE_NINJA_IDLE;
				this->m_Position.y += this->m_Collision->m_MoveY;
				m_Physic->setVelocityX(0.0f);
				return 0;
			}
			else
			{
				if (m_ObjectState == STATE_NINJA_HANG || m_ObjectState == STATE_NINJA_CLIMB)
				{
					m_Physic->setVelocityX(0.0f);
					return 0;
				}
				else {
					isJump = false;
					this->m_Position.y += this->m_Collision->m_MoveY;
					m_Physic->setVelocityY(0.0f);
					return 0;
				}
			}
		}


		return 0;
	}
	else if (collideDirection == IDDirection::DIR_BOTTOM)
	{

		if (m_ignoreCollisionObject == checkingObject)
		{
			m_ignoreCollisionObject = 0;
		}
		return 0;
	}

	else if (collideDirection == IDDirection::DIR_LEFT)
	{
		return 0;
	}

	else if (collideDirection == IDDirection::DIR_RIGHT)
	{
		return 0;
	}
	return 1;
}

void Ninja::UpdateCollision(CObjectDx9* checkingObject)
{
	setRectangleCheckingObjectBelow();
	IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);
	
	if (collideDirection != IDDirection::DIR_NONE)
	{
		switch (checkingObject->getTypeObject())
		{
		case ETypeObject::VIRTUAL_OBJECT:
		{
			switch (checkingObject->getID())
			{
			case eObjectID::TILE_BASE:
				
#pragma region TILE_BASE
			{
				UpdateCollisionTileBase(collideDirection, checkingObject);
			}
			break;
			case eObjectID::VIRTUAL_OBJECT_WALL:
			{
				if (collideDirection == IDDirection::DIR_RIGHT)
				{
					if (m_ObjectState == eObjectState::STATE_NINJA_RUN)
					{
						this->m_Position.x += this->m_Collision->m_MoveX;
						m_Physic->setVelocityX(0.0f);
					}
					if (m_ObjectState == eObjectState::STATE_NINJA_JUMP)
					{
						SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_NINJA_CLIMB)->Play();
						m_ObjectState = eObjectState::STATE_NINJA_HANG;
						this->m_Position.x += this->m_Collision->m_MoveX;
						m_Physic->setVelocityX(0.0f);
					}
				}
				if (collideDirection == IDDirection::DIR_LEFT)
				{
					if (m_ObjectState == eObjectState::STATE_NINJA_RUN)
					{
						this->m_Position.x += this->m_Collision->m_MoveX;
						m_Physic->setVelocityX(0.0f);
					}
					if (m_ObjectState == eObjectState::STATE_NINJA_JUMP)
					{
						SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_NINJA_CLIMB)->Play();
						m_ObjectState = eObjectState::STATE_NINJA_HANG;
						this->m_Position.x += this->m_Collision->m_MoveX;
						m_Physic->setVelocityX(0.0f);
					}
				}
			}
			case eObjectID::VIRTUAL_OBJECT_CLIMB:
			{
				maxClimb = checkingObject->getBound().top+31;
				minClimb = checkingObject->getBound().bottom+31;
				if (collideDirection == IDDirection::DIR_RIGHT)
				{
					if (m_ObjectState == eObjectState::STATE_NINJA_JUMP)
					{
						m_ObjectState = eObjectState::STATE_NINJA_HANG;
						this->m_Position.x += this->m_Collision->m_MoveX;
						m_Physic->setVelocityX(0.0f);
						isClimb = true;
					}
				}
				if (collideDirection == IDDirection::DIR_LEFT)
				{
					if (m_ObjectState == eObjectState::STATE_NINJA_JUMP)
					{
						m_ObjectState = eObjectState::STATE_NINJA_HANG;
						this->m_Position.x += this->m_Collision->m_MoveX;
						m_Physic->setVelocityX(0.0f);
						isClimb = true;
					}
				}
			}
			default:
				break;
			}
		}
		default:
			switch (checkingObject->getID())
			{
			case eObjectID::ENEMY_RUN:
			case eObjectID::ENEMY_BROWN_BAT:
			case eObjectID::BOSS_3:
			case eObjectID::ENEMY_PANTHER:
			case eObjectID::ENEMY_EAGLE:
			case eObjectID::ENEMY_MACHINE_GUN:
			case eObjectID::BULLET_ENEMY:
			case eObjectID::ENEMY_ROCKET:
			case eObjectID::ENEMY_THROW_SWORD:
			case eObjectID::ENEMY_SWORD:
				if (isInvulnerable)
				{
					break;
				}
				if (checkingObject->getObjectState() != eObjectState::STATE_BEFORE_DEATH && checkingObject->getObjectState() != eObjectState::STATE_DEATH)
				{
					SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_NINJA_HITTED)->Play();
					CGlobal::healthNinja--;
					m_ObjectState = eObjectState::STATE_NINJA_DEAD;
				}
				break;
			case eObjectID::SKILL_NINJA:
			{
				Skill* temp = (Skill*)checkingObject;
				if (temp->getObjectState() != eObjectState::STATE_DEATH)
				{
					if (temp->getLivingTime() > 600)
					{
						temp->setObjectState(eObjectState::STATE_DEATH);
						temp->reset();
					}
				}
			}
			default:
				break;
			}
			break;
		}
	}
	CGlobal::Item = m_SkillNinja;
}
void Ninja::Update()
{

}
void Ninja::Render(SPRITEHANDLE spriteHandle)
{
	
	D3DXCOLOR color;
	if (isInvulnerable)
	{
		color = D3DCOLOR_ARGB(m_colorAlpha, 0xff, 0xff, 0xff);
	}
	else
	{
		color = D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff);
	}
	if (m_Direction == eDirection::RIGHT)
	{
		m_NinjaSprite->Render(spriteHandle,
			getPositionVec2(),
			ESpriteEffect::None,
			0.0f,
			1.0f,
			1.0f,
			color);
		return;
	}
	if (m_Direction == eDirection::LEFT)
	{
		m_NinjaSprite->Render(spriteHandle,
			getPositionVec2(),
			ESpriteEffect::Horizontally,
			0.0f,
			1.0f,
			1.0f,
			color);
		return;
	}
}
void Ninja::SetFallFlag()
{
	switch (m_ObjectState)
	{
	
	case STATE_NINJA_FALL:
		isFall = true;
		break;
	case STATE_NINJA_HIT:
	case STATE_NINJA_IDLE:
	case STATE_NINJA_RUN:
	case STATE_NINJA_JUMP:
		isClimb = false;
	case STATE_NINJA_CLIMB:
		isFall = false;
		break;
	default:
		break;
	}
}
void Ninja::SetVelocityXZero()
{
	switch (m_ObjectState)
	{
	case STATE_NINJA_SKILL:
	case STATE_NINJA_HIT:
		if(isJump==false) m_Physic->setVelocityX(0.0f);
	case STATE_NINJA_JUMP:
		return;
	
	case STATE_NINJA_IDLE:
	case STATE_NINJA_FALL:
	case STATE_NINJA_HANG:
		m_Physic->setVelocityX(0.0f);
		return;
	default:
		break;
	}
}

void Ninja::SetVelocityYZero()
{
	switch (m_ObjectState)
	{
	case STATE_NINJA_IDLE:
	case STATE_NINJA_JUMP:
	case STATE_NINJA_FALL:
	case STATE_NINJA_HIT:
	case STATE_NINJA_RUN:
		return;
	case STATE_NINJA_HANG:
		m_Physic->setVelocityY(0.0f);
		return;
	default:
		break;
	}
}
void Ninja::SetFlag()
{
	SetFallFlag();
	SetVelocityXZero();
	SetVelocityYZero();
}
void Ninja::setRectangleCheckingObjectBelow()
{
	m_RectangleCheckingObjectBelow.left = (long)(int)(m_Position.x - 5);
	m_RectangleCheckingObjectBelow.top = (long)(int)(m_Position.y - 17);

	m_RectangleCheckingObjectBelow.right = (long)(int)(m_Position.x + 5);
	m_RectangleCheckingObjectBelow.bottom = (long)(int)(0);
}
void Ninja::Release()
{

}
Ninja::~Ninja()
{
}
