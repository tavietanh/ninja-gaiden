#include "Point1000.h"

Point1000::Point1000()
{

}

Point1000::Point1000(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void Point1000::Initialize()
{
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_1000_POINT));
	m_ObjectState = STATE_ALIVE_IDLE;
	m_Position.z = 1.0f;
}

void Point1000::UpdateAnimation()
{
}


void Point1000::UpdateCollision(CObjectDx9* checkingObject)
{
	if (!isDead)
	{
		IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);
		if (collideDirection != IDDirection::DIR_NONE)
		{
			switch (checkingObject->getID())
			{
			case eObjectID::NINJA:
			{
				Ninja* temp = (Ninja*)checkingObject;
				if (temp->getObjectState() == eObjectState::STATE_NINJA_IDLE || temp->getObjectState() == STATE_NINJA_RUN)
				{
					isDead = true;
					temp->SetInvulnerable(true);
					temp->setItemNinja(eIDItem::ITEM_1000_POINT);
					SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_NINJA_COLLECT)->Play();
					CGlobal::score += 1000;
					this->m_ObjectState = STATE_DEATH;
				}
			}
			break;
			case eObjectID::TILE_BASE:
				if (collideDirection == IDDirection::DIR_TOP)
				{
					if (getPhysic()->getVelocity().y <= 0)
					{
						getPhysic()->setVelocity(D3DXVECTOR2(0.0f, 0.0f));
					}
				}
				break;
			default:
				break;
			}

		}
	}
}


void Point1000::UpdateMovement()
{
	m_Physic->UpdateMovement(&m_Position);
}

void Point1000::Update()
{
	if (m_ObjectState == STATE_DEATH)
	{
		if (isDead)
		{
			Release();
		}
	}
}

void Point1000::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite)
	{
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}

void Point1000::Release()
{
	isDead = true;
	m_Sprite->Release();
	SAFE_DELETE(m_Sprite);
}

Point1000::~Point1000()
{

}
