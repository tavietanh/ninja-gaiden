#include "EnemyThrowSword.h"

#define VELOC_MOVE_RIGHT 0.3f
#define VELOC_MOVE_LEFT -0.3f
#define VELOC_JUMB	0.8f

EnemyThrowSword::EnemyThrowSword()
{
}

EnemyThrowSword::EnemyThrowSword(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void EnemyThrowSword::Initialize()
{
	isDead = false;
	m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOSION));
	sprite_alivemove = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_ENEMY_THROW_SWORD_MOVE));
	sprite_shoot = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_ENEMY_THROW_SWORD_SHOOT));
	m_Sprite = sprite_alivemove;
	m_TimeChangeState = 0;
	m_TimeChangeDirectAttack = 0;
	this->m_Physic->setVelocity(D3DXVECTOR2(0, 0));
	this->m_Physic->setAccelerate(D3DXVECTOR2(0, -0.01f));
	m_Position.z = 1.0f;
	if (m_Position.x > CGlobal::Ninja_X)
	{
		m_Physic->setVelocityX(VELOC_MOVE_LEFT);
		m_Direction = eDirection::LEFT;
	}
	else
	{
		m_Direction = eDirection::RIGHT;
		m_Physic->setVelocityX(VELOC_MOVE_RIGHT);
	}
	rangeofMovementLeft = m_Position.x - SCREEN_WIDTH/ 6;
	rangeofMovementRight= m_Position.x + SCREEN_WIDTH / 6;
}
D3DXVECTOR3 EnemyThrowSword::GetStartPositionOfSkill(float x, float y)
{
	return D3DXVECTOR3(m_Position.x + x, m_Position.y + y, 0);
}
void EnemyThrowSword::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		m_Sprite = sprite_alivemove;
		break;
	case STATE_ALIVE_MOVE:
		m_Sprite = sprite_alivemove;
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_BEFORE_DEATH:
		m_Sprite = sprite_dead;
		break;
	case STATE_DEATH:
		break;
	case STATE_SHOOTING:
		m_Sprite = sprite_shoot;
	default:
		break;
	}
}


void EnemyThrowSword::UpdateCollision(CObjectDx9* checkingObject)
{
	if (isDead != true)
	{
		IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

		if (collideDirection != IDDirection::DIR_NONE)
		{
			switch (checkingObject->getID())
			{
			case eObjectID::SKILL_NINJA:
			{
				Skill* temp = (Skill*)checkingObject;
				if (temp->getTypeSkill() != eIDTypeSkill::NINJA_WINDMIL_STAR)
					temp->setObjectState(eObjectState::STATE_DEATH);
				SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_EXPLOSION)->Play();
				CGlobal::score += 200;
				this->m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
				this->getPhysic()->setVelocityY(0.0f);
				this->getPhysic()->setVelocityX(0.0f);
				this->isDead = true;
				break;
			}
			case eObjectID::TILE_BASE:
				if (m_Position.y > checkingObject->getPositionVec3().y)
				{
					if (collideDirection == IDDirection::DIR_TOP)
					{
						this->m_Position.y += this->m_Collision->m_MoveY;
						this->m_Physic->setVelocityY(0.0f);
						if (this->getBound().left <= checkingObject->getBound().left)
						{
							m_Physic->setVelocityX(VELOC_MOVE_RIGHT);
						}
						if (this->getBound().right >= checkingObject->getBound().right)
						{
							m_Physic->setVelocityX(VELOC_MOVE_LEFT);
						}
					}
				}
				break;
			default:
				break;
			}
		}
	}
}
void EnemyThrowSword::UpdateMovement()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_ALIVE_MOVE:
		if (m_Position.x>CGlobal::Ninja_X)
			m_Direction = eDirection::LEFT;
		else m_Direction = eDirection::RIGHT;
		if (m_Position.x < rangeofMovementLeft)
		{
			m_Physic->setVelocityX(VELOC_MOVE_RIGHT);
		}
		if (m_Position.x > rangeofMovementRight)
		{
			m_Physic->setVelocityX(VELOC_MOVE_LEFT);
		}
		if (m_Position.x < 0 /*|| m_Position.x > Camera::getInstance()->getBound().right*/)
		{
			m_ObjectState = eObjectState::STATE_DEATH;
			isDead = true;
		}
		break;
	case STATE_SHOOTING:
		break;
	case STATE_BEFORE_DEATH:
		if (isDead == false)
		{
			if (m_Position.x < rangeofMovementLeft)
			{
				m_Physic->setVelocityX(VELOC_MOVE_RIGHT);
			}
			if(m_Position.x > rangeofMovementRight)
			{
				m_Physic->setVelocityX(VELOC_MOVE_LEFT);
			}
			m_Physic->setVelocityY(VELOC_JUMB);
			m_Physic->setAccelerate(D3DXVECTOR2(0, 0));
			isDead = true;
		}
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}

	m_Physic->UpdateMovement(&m_Position);
}
void EnemyThrowSword::Update()
{
	switch (this->m_ObjectState)
	{
	case STATE_SHOOTING:
		if (isShoot)
		{
			m_TimeChangeDirectAttack += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeDirectAttack > 400)
			{
				if (m_Direction == eDirection::LEFT)
				{
					SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::ENEMY_BULLET, GetStartPositionOfSkill(0, 14), D3DXVECTOR2(-0.8f, 2.0f), 0);
				}
				else 
					SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::ENEMY_BULLET, GetStartPositionOfSkill(0, 14), D3DXVECTOR2(0.8f, 2.0f), 0);
				isShoot = false;
				m_Physic->setVelocityX(preVelocity.x);
				m_Position.y = m_Position.y - 5;
				m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
				m_TimeChangeDirectAttack = 0;
			}
			
		}
		break;
	case STATE_ALIVE_IDLE:
		break;
	case STATE_ALIVE_MOVE:
		m_TimeChangeDirectAttack += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_TimeChangeDirectAttack > 3000)
		{

			m_TimeChangeDirectAttack = 0;
			preVelocity = m_Physic->getVelocity();
			m_Physic->setVelocityX(0.0f);
			m_Position.y = m_Position.y + 5;
			m_ObjectState = eObjectState::STATE_SHOOTING;
			isShoot = true;
		}
		break;
	case STATE_BEFORE_DEATH:
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
	case STATE_DEATH:
		this->Release();
		break;
	default:
		break;
	}

}

void EnemyThrowSword::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite != NULL)
	{
		if (m_Direction == eDirection::LEFT)
			m_Sprite->setSpriteEffect(ESpriteEffect::Horizontally);
		else
		{
			m_Sprite->setSpriteEffect(ESpriteEffect::None);
		}

		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}

void EnemyThrowSword::Release()
{
	this->m_Position = this->m_SPosition;
	this->Initialize();
}
EnemyThrowSword::~EnemyThrowSword()
{
}


