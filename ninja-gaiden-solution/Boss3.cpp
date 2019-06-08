#include "Boss3.h"

#define VELOC_MOVE_RIGHT 1.3f
#define VELOC_MOVE_LEFT -1.3f
#define VELOC_JUMB	3.0f

Boss3::Boss3()
{
}

Boss3::Boss3(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void Boss3::Initialize()
{
	isDead = false;
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOSION));
	sprite_jump = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOSS));
	m_Sprite = sprite_jump;
	m_TimeChangeState = 0;
	m_TimeChangeDirectAttack = 0;
	countBullet = 0;
	healthBoss = 16;
	turnjump = VELOC_MOVE_LEFT;
	this->m_Physic->setVelocity(D3DXVECTOR2(0, 0));
	this->m_Physic->setAccelerate(D3DXVECTOR2(0, -0.05f));
	m_Position.z = 1.0f;
	isJump = false;
	if (m_Position.x > CGlobal::Ninja_X)
	{
		m_Direction = eDirection::LEFT;
	}
	else
	{
		m_Direction = eDirection::RIGHT;
	}
}
D3DXVECTOR3 Boss3::GetStartPositionOfSkill(float x, float y)
{
	return D3DXVECTOR3(m_Position.x + x, m_Position.y + y, 0);
}
void Boss3::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		m_Sprite = sprite_jump;
		m_Sprite->getAnimation()->setCurrentFrame(0);
		break;
	case STATE_JUMP:
		m_Sprite = sprite_jump;
		m_Sprite->getAnimation()->setCurrentFrame(1);
		break;
	case STATE_BEFORE_DEATH:
		m_Sprite = sprite_dead;
		break;
	case STATE_DEATH:
		break;
	case STATE_SHOOTING:
		m_Sprite = sprite_jump;
		m_Sprite->getAnimation()->setCurrentFrame(0);
	default:
		break;
	}
}


void Boss3::UpdateCollision(CObjectDx9* checkingObject)
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
				temp->setObjectState(eObjectState::STATE_DEATH);
				healthBoss--;
				char key[255];
				sprintf_s(key, "FPS: %.3f \n", healthBoss);
				OutputDebugString(key);
				if(healthBoss==0)
				{
					this->m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
					this->getPhysic()->setVelocityY(0.0f);
					this->getPhysic()->setVelocityX(0.0f);
					this->isDead = true;
				}

				break;
			}
			case eObjectID::TILE_BASE:
				if (m_Position.y > checkingObject->getPositionVec3().y)
				{
					if (collideDirection == IDDirection::DIR_TOP)
					{
						if (m_ObjectState == STATE_JUMP )
						{
							if (m_Physic->getVelocity().y < 0)
							{
								if (m_ObjectState == STATE_JUMP)
								{
									m_ObjectState = STATE_ALIVE_IDLE;
									this->m_Position.y += this->m_Collision->m_MoveY;
									m_Physic->setVelocityY(0.0f);
									m_Physic->setVelocityX(0.0f);
								}
							}
						}
						else
						{
							this->m_Position.y += this->m_Collision->m_MoveY;
							this->m_Physic->setVelocityY(0.0f);
							m_Physic->setVelocityX(0.0f);
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
void Boss3::UpdateMovement()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		if (m_Position.x>CGlobal::Ninja_X)
			m_Direction = eDirection::LEFT;
		else m_Direction = eDirection::RIGHT;
		break;
	case STATE_JUMP:
		if (isJump)
		{
			m_Physic->setVelocityY(VELOC_JUMB);
			m_Physic->setVelocityX(turnjump);
			turnjump = -turnjump;

			isJump = false;
		}
		
		break;
	case STATE_SHOOTING:
		break;
	case STATE_BEFORE_DEATH:
		if (isDead == false)
		{
			m_Physic->setVelocityY(0.0f);
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
void Boss3::Update()
{
	switch (this->m_ObjectState)
	{
	case STATE_SHOOTING:

		break;
	case STATE_ALIVE_IDLE:
		m_TimeChangeDirectAttack += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_TimeChangeDirectAttack > 1000)
		{
			m_TimeChangeDirectAttack = 0;
			isJump = true;
			if (countBullet == 1 || countBullet == 5 || countBullet == 8)
			{
				if (m_Direction == eDirection::LEFT)
				{
					SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::ENEMY_BULLET, GetStartPositionOfSkill(10, -15), D3DXVECTOR2(-0.8f, 2.0f), 3);
					SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::ENEMY_BULLET, GetStartPositionOfSkill(0, 0), D3DXVECTOR2(-0.8f, 2.0f), 3);
					SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::ENEMY_BULLET, GetStartPositionOfSkill(-10, 15), D3DXVECTOR2(-0.8f, 2.0f), 3);
				}
				else
				{
					SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::ENEMY_BULLET, GetStartPositionOfSkill(-10, -15), D3DXVECTOR2(0.8f, 2.0f), 3);
					SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::ENEMY_BULLET, GetStartPositionOfSkill(0, 0), D3DXVECTOR2(0.8f, 2.0f), 3);
					SkillManager::getInstance()->addSkillIntoList(eIDTypeSkill::ENEMY_BULLET, GetStartPositionOfSkill(10, 15), D3DXVECTOR2(0.8f, 2.0f), 3);
				}
			}
			if (countBullet == 10)
			{
				countBullet = 0;
			}
			countBullet++;
			m_ObjectState = eObjectState::STATE_JUMP;
		}
		break;
	case STATE_JUMP:
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

void Boss3::Render(SPRITEHANDLE spriteHandle)
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

void Boss3::Release()
{
	this->m_Position = this->m_SPosition;
	this->Initialize();
}
Boss3::~Boss3()
{
}


