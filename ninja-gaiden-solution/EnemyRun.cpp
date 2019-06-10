#include "EnemyRun.h"

#define VELOC_MOVE_RIGHT 0.6f
#define VELOC_MOVE_LEFT -0.6f
#define VELOC_JUMB	0.3f

EnemyRun::EnemyRun()
{
}

EnemyRun::EnemyRun(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void EnemyRun::Initialize()
{
	isDead = false;
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOSION));
	sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_ENEMY_RUN));
	m_Sprite = sprite_main;
	isJumb = false;
	m_TimeChangeState = 0;
	this->m_Physic->setVelocity(D3DXVECTOR2(0, 0));
	this->m_Physic->setAccelerate(D3DXVECTOR2(0, -0.01f));
	m_Position.z = 1.0f;
	if (m_Position.x>CGlobal::Ninja_X)
		m_Direction = eDirection::LEFT;
	else m_Direction = eDirection::RIGHT;
}

void EnemyRun::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		m_Sprite = sprite_main;
		break;
	case STATE_ALIVE_MOVE:
		m_Sprite = sprite_main;
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_BEFORE_DEATH:
		m_Sprite = sprite_dead;
		break;
	case STATE_DEATH:
		break;
	case STATE_JUMP:
		m_Sprite = sprite_main;
		m_Sprite->UpdateAnimation(250);
	default:
		break;
	}
}

void EnemyRun::UpdateCollision(CObjectDx9* checkingObject)
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
						m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
						this->isJumb = false;
						this->m_Position.y += this->m_Collision->m_MoveY;
						this->m_Physic->setVelocityY(0.0f);

						if (this->getBound().left <= checkingObject->getBound().left)
						{
							m_Physic->setVelocityY(VELOC_JUMB);
							m_ObjectState = eObjectState::STATE_JUMP;
						}
						if (this->getBound().right >= checkingObject->getBound().right)
						{
							m_Physic->setVelocityY(VELOC_JUMB);
							m_ObjectState = eObjectState::STATE_JUMP;
						}
					}
					else
					{
						this->isJumb = true;
					}
				}
				break;
			case eObjectID::VIRTUAL_OBJECT_WALL:
				if (collideDirection == IDDirection::DIR_RIGHT) {
					m_Physic->setVelocityY(1.1f);
					m_ObjectState = eObjectState::STATE_JUMP;
				}
				if (collideDirection == IDDirection::DIR_LEFT) {
					m_Physic->setVelocityY(1.1f);
					m_ObjectState = eObjectState::STATE_JUMP;
				}
			default:
				break;
			}
		}
	}
}
void EnemyRun::UpdateMovement()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_ALIVE_MOVE:
		if (m_Direction == eDirection::LEFT)
		{
			m_Physic->setVelocityX(VELOC_MOVE_LEFT);
		}
		else
		{
			m_Physic->setVelocityX(VELOC_MOVE_RIGHT);
		}
		if (m_Position.x < 0 /*|| m_Position.x > Camera::getInstance()->getBound().right*/)
		{
			m_ObjectState = eObjectState::STATE_DEATH;
			isDead = true;
		}
		break;
	case STATE_JUMP:
	{
		this->m_Physic->setAccelerateY(-0.01f);
	}
	break;
	case STATE_BEFORE_DEATH:
		if (isDead == false)
		{
			if (m_Direction == eDirection::LEFT)
			{
				m_Physic->setVelocityX(-VELOC_MOVE_LEFT);
			}
			else
			{
				m_Physic->setVelocityX(-VELOC_MOVE_RIGHT);
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
void EnemyRun::Update()
{
	switch (this->m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_ALIVE_MOVE:
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

void EnemyRun::Render(SPRITEHANDLE spriteHandle)
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

void EnemyRun::Release()
{
	this->m_Position = this->m_SPosition;
	this->Initialize();
}
EnemyRun::~EnemyRun()
{
}
