#include "GifButerfly.h"

GifButerfly::GifButerfly()
{

}

GifButerfly::GifButerfly(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID, eObjectID _idItem)
	: DynamicObject(_position, _direction, _objectID)
{
	m_IDItem = _idItem;
}

void GifButerfly::Initialize()
{
	m_Position.z = 1.0f;
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_alive = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_GIF_BUTERFLY));
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOSION));
	m_Sprite = sprite_alive;
	isDead = false;
}

void GifButerfly::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		m_Sprite = sprite_alive;
		m_Sprite->UpdateAnimation(200);
		break;
	case STATE_BEFORE_DEATH:
		if (!isDead)
		{
			m_Sprite = sprite_dead;
			isDead = true;
		}
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
}


void GifButerfly::UpdateCollision(CObjectDx9* checkingObject)
{
	if (!isDead)
	{
		if (checkingObject->getID() == eObjectID::SKILL_NINJA)
		{
			IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);
			if (collideDirection != IDDirection::DIR_NONE)
			{
				Skill* temp = (Skill*)checkingObject;
				if (temp->getTypeSkill() != eIDTypeSkill::NINJA_WINDMIL_STAR)
					temp->setObjectState(eObjectState::STATE_DEATH);
				SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_EXPLOSION)->Play();
				m_ObjectState = STATE_BEFORE_DEATH;

				if (m_IDItem == eObjectID::OBJECT_THROW_STAR)
				{
					ItemManager::getInstance()->AddElement(new ThrowStar(m_Position, eDirection::RIGHT, eObjectID::OBJECT_THROW_STAR));
				}
				if (m_IDItem == eObjectID::OBJECT_FLAMES)
				{
					ItemManager::getInstance()->AddElement(new Flames(m_Position, eDirection::RIGHT, eObjectID::OBJECT_FLAMES));
				}
				if (m_IDItem == eObjectID::OBJECT_WINDMIL_STAR)
				{
					ItemManager::getInstance()->AddElement(new WindMilStar(m_Position, eDirection::RIGHT, eObjectID::OBJECT_WINDMIL_STAR));
				}
				if (m_IDItem == eObjectID::OBJECT_1000_POINT)
				{
					ItemManager::getInstance()->AddElement(new Point1000(m_Position, eDirection::RIGHT, eObjectID::OBJECT_1000_POINT));
				}
				if (m_IDItem == eObjectID::OBJECT_10_POWER)
				{
					ItemManager::getInstance()->AddElement(new TenPower(m_Position, eDirection::RIGHT, eObjectID::OBJECT_10_POWER));
				}
				if (m_IDItem == eObjectID::OBJECT_500_POINT)
				{
					ItemManager::getInstance()->AddElement(new Point500(m_Position, eDirection::RIGHT, eObjectID::OBJECT_500_POINT));
				}
				if (m_IDItem == eObjectID::OBJECT_5_POWER)
				{
					ItemManager::getInstance()->AddElement(new FivePower(m_Position, eDirection::RIGHT, eObjectID::OBJECT_5_POWER));
				}
				if (m_IDItem == eObjectID::OBJECT_HEALTH)
				{
					ItemManager::getInstance()->AddElement(new Health(m_Position, eDirection::RIGHT, eObjectID::OBJECT_HEALTH));
				}
				if (m_IDItem == eObjectID::OBJECT_TIME_FREEZE)
				{
					ItemManager::getInstance()->AddElement(new Freeze(m_Position, eDirection::RIGHT, eObjectID::OBJECT_TIME_FREEZE));
				}
			}
		}
	}
}

void GifButerfly::UpdateMovement()
{
}
void GifButerfly::Update()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_BEFORE_DEATH:
		if (isDead)
		{
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeState > 200)
			{
				m_Sprite->setScale(m_Sprite->getScale()*1.5f);
			}
			if (m_TimeChangeState > 215)
			{
				m_TimeChangeState = 0;
				m_ObjectState = eObjectState::STATE_DEATH;
			}
		}
		break;
	case STATE_DEATH:
		this->Release();
		break;
	default:
		break;
	}
}
void GifButerfly::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite != 0)
	{
		m_Sprite->Render(spriteHandle,
			getPositionVec2(),
			m_Sprite->getSpriteEffect(),
			m_Sprite->getRotate(),
			m_Sprite->getScale(),
			m_Position.z);
	}
}


void GifButerfly::Release()
{
}

GifButerfly::~GifButerfly()
{

}

