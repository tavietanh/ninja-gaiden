#include "CObjectDx9.h"

int CObjectDx9::m_identifyNumber = 0;

CObjectDx9::CObjectDx9()
{
}

RECT CObjectDx9::getBound()
{
	RECT tempBound = RECT();

	tempBound.left = (long)(m_Position.x - m_Sprite->getAnimation()->getFrameSize().x / 2);
	tempBound.right = (long)(tempBound.left + m_Sprite->getAnimation()->getFrameSize().x);
	tempBound.top = (long)(m_Position.y + m_Sprite->getAnimation()->getFrameSize().y / 2);
	tempBound.bottom = (long)(tempBound.top - m_Sprite->getAnimation()->getFrameSize().y);

	return tempBound;
}

CObjectDx9::CObjectDx9(D3DXVECTOR3 _position,eDirection _direction)
{
	m_Position = _position;
	m_Direction = _direction;
}

CObjectDx9::~CObjectDx9()
{
}
