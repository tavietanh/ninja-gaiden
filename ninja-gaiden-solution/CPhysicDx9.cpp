#include "CPhysicDx9.h"

CPhysicDx9::CPhysicDx9()
{
	//m_Position		= D3DXVECTOR3(400, 300, 0);
	m_Velocity = D3DXVECTOR2(0, 0);
	m_Accelerate = D3DXVECTOR2(0, 0);
}

bool CPhysicDx9::CheckMovementRangeWidth(D3DXVECTOR3* _position)
{
	if (m_MovementRange != 0)
	{
		if (_position->x < m_MovementRange->left || _position->x > m_MovementRange->right)
		{
			return true;
		}
	}
	return false;
}

bool CPhysicDx9::CheckMovementRangeHeight(D3DXVECTOR3* _position)
{
	if (m_MovementRange != 0)
	{
		if (_position->y < m_MovementRange->bottom || _position->y > m_MovementRange->top)
		{
			return true;
		}
	}
	return false;
}

void CPhysicDx9::UpdateMovement(D3DXVECTOR3* _position)
{
	if (CheckMovementRangeWidth(_position))
	{
		m_Velocity.x *= -1.0f;
	}
	if (CheckMovementRangeHeight(_position))
	{
		m_Velocity.y *= -1.0f;
	}

	float deltaTime = (float)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds() / 1000;

	deltaTime = deltaTime / ((float)1 / FRAME_RATE);

	_position->x += m_Velocity.x * deltaTime;
	_position->y += m_Velocity.y * deltaTime;
	m_Velocity.x += m_Accelerate.x * deltaTime;
	m_Velocity.y += m_Accelerate.y * deltaTime;
}

void CPhysicDx9::CheckCollision(CObjectDx9* _object)
{

}

CPhysicDx9::~CPhysicDx9()
{

}
