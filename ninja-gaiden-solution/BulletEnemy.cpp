#include "BulletEnemy.h"


BulletEnemy::BulletEnemy()
{

}
BulletEnemy::BulletEnemy(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) : Skill(_position, _direction, _objectID)
{
	this->m_Position.z = 1.0f;
}

void BulletEnemy::Initialize()
{
	this->sprite_boss = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BOSS));
	this->sprite_rocket = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_ENEMY_ROCKET));
	this->sprite_gun = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_ENEMY_MACHINE_GUN));
	this->sprite_sword = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SWORD_ENEMY_THROW));
	this->m_Sprite = sprite_sword;
	this->m_Position.z = 0.0f;
	this->m_Physic->setVelocityX(1.0f);
	this->m_Physic->setAccelerate(D3DXVECTOR2(0.0f, 0.0f));
	this->m_TypeSkill = eIDTypeSkill::ENEMY_BULLET;
	this->m_DirectAttack = eDirectAttack::AD_TOP;
	this->m_factor = 0;
	this->isDead = false;
}

void BulletEnemy::UpdateMovement()
{

	Skill::UpdateMovement();
	D3DXVECTOR3 tempPosition;

	if (this->m_factor == 1 || this->m_factor == 2|| this->m_factor == 3 )
	{
		this->getPhysic()->setVelocityY(0.0f);
	}
	if (this->m_factor == 0)
	{
		float i = m_Sprite->getRotate();
		m_Sprite->setRotate(i + 10);
		this->getPhysic()->setAccelerateY(-0.1f);
	}
}
void BulletEnemy::UpdateAnimation()
{
	if (eObjectState::STATE_DEATH || eObjectState::STATE_ALIVE_MOVE)
	{
		if (m_factor == 0)
			m_Sprite = sprite_sword;
		if (m_factor == 1)
			m_Sprite = sprite_gun;
		if (m_factor == 2)
			m_Sprite = sprite_rocket;
		if (m_factor == 3)
			m_Sprite = sprite_boss;
		if (getPhysic()->getVelocity().x > 0)
		{
			m_Sprite->setSpriteEffect(ESpriteEffect::None);
		}
		else m_Sprite->setSpriteEffect(ESpriteEffect::Horizontally);
	}
	Skill::UpdateAnimation();

}
void BulletEnemy::UpdateCollision(CObjectDx9* checkingObject)
{
	if (!isDead)
	{
		IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);
		if (collideDirection != IDDirection::DIR_NONE)
		{
			switch (checkingObject->getID())
			{
			case eObjectID::SKILL_NINJA:
			{
				Skill* temp = (Skill*)checkingObject;
					isDead = true;
					this->getPhysic()->setVelocityX(0.0f);
					this->getPhysic()->setVelocityY(0.0f);
					this->m_ObjectState = STATE_BEFORE_DEATH;
			}
			break;
			default:
				break;
			}

		}
	}
}
BulletEnemy::~BulletEnemy()
{

}

