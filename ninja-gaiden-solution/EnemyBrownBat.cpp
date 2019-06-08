#include "EnemyBrownBat.h"

#define VELOC_MOVE_RIGHT 2.0f
#define VELOC_MOVE_LEFT -2.0f
#define VELOC_MOVE_UP -0.3f
#define ACCELRATE	-0.03f

EnemyBrownBat::EnemyBrownBat()
{
}

EnemyBrownBat::EnemyBrownBat(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void EnemyBrownBat::Initialize()
{
	isDead = false;
	m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOSION));
	sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_ENEMY_BROWN_BAT));
	m_Sprite = sprite_main;
	isJumb = false;
	m_TimeChangeState = 0;
	this->m_Physic->setVelocity(D3DXVECTOR2(0, 0));
	m_Position.z = 1.0f;
	if (m_Position.x>CGlobal::Ninja_X)
		m_Direction = eDirection::LEFT;
	else m_Direction = eDirection::RIGHT;
}

void EnemyBrownBat::UpdateAnimation()
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
	default:
		break;
	}
}

void EnemyBrownBat::UpdateCollision(CObjectDx9* checkingObject)
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
				this->m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
				this->getPhysic()->setVelocityY(0.0f);
				this->getPhysic()->setVelocityX(0.0f);
				this->isDead = true;
				break;
			}
			default:
				break;
			}
		}
	}
}
void EnemyBrownBat::UpdateMovement()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_ALIVE_MOVE:
	{
		if (m_Position.x > CGlobal::Ninja_X)
			m_Direction = eDirection::LEFT;
		else m_Direction = eDirection::RIGHT;
		D3DXVECTOR3 temp = m_Physic->getVelocity();
		float m_factory = ACCELRATE / 10;
		int distancey = (CGlobal::Ninja_Y + 8) - ceil(this->m_Position.y);
		if (distancey > 0)
		{
			this->getPhysic()->setAccelerateY(-m_factory);
			if (temp.y < VELOC_MOVE_UP) m_Physic->setVelocityY(VELOC_MOVE_UP);
		}
		else if (distancey < 0)
			this->getPhysic()->setAccelerateY(m_factory);
		else if (distancey == 0)
			this->getPhysic()->setAccelerateY(0);
		if (CGlobal::Ninja_X - ceil(this->m_Position.x) > 0)
		{
			this->getPhysic()->setAccelerateX(-ACCELRATE);
			if (temp.x < VELOC_MOVE_LEFT) m_Physic->setVelocityX(VELOC_MOVE_LEFT);
		}
		else {
			this->getPhysic()->setAccelerateX(ACCELRATE);
			if (temp.x > VELOC_MOVE_RIGHT) m_Physic->setVelocityX(VELOC_MOVE_RIGHT);
		}
	}
	break;
	case STATE_JUMP:
		break;
	case STATE_BEFORE_DEATH:
		if (isDead == false)
		{
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
void EnemyBrownBat::Update()
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

void EnemyBrownBat::Render(SPRITEHANDLE spriteHandle)
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

void EnemyBrownBat::Release()
{
	this->m_Position = this->m_SPosition;
	this->Initialize();
}
EnemyBrownBat::~EnemyBrownBat()
{
}
