#include "Flames.h"

Flames::Flames()
{

}

Flames::Flames(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void Flames::Initialize()
{
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_FLAMES));
	m_ObjectState = STATE_ALIVE_IDLE;
	m_Position.z = 1.0f;
}

void Flames::UpdateAnimation()
{
}


void Flames::UpdateCollision(CObjectDx9* checkingObject)
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
				isDead = true;
				Ninja* temp = (Ninja*)checkingObject;
				temp->SetInvulnerable(true);
				this->m_ObjectState = STATE_DEATH;
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


void Flames::UpdateMovement()
{
	m_Physic->UpdateMovement(&m_Position);
}

void Flames::Update()
{
	if (m_ObjectState == STATE_DEATH)
	{
		if (isDead)
		{
			Release();
		}
	}
}

void Flames::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite)
	{
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}

void Flames::Release()
{
	isDead = true;
	m_Sprite->Release();
	SAFE_DELETE(m_Sprite);
}

Flames::~Flames()
{

}
