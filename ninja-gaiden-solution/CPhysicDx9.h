#ifndef PHYSIC_H
#define PHYSIC_H

#include "CObjectDx9.h"
#include "CGameTimeDx9.h"
#include "EDirection.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

class CObjectDx9;

using namespace std;


class ObjectState;

class CPhysicDx9
{
	D3DXVECTOR2			m_Velocity;
	D3DXVECTOR2			m_Accelerate;
	eDirection			m_Direction;
	RECT*				m_MovementRange;

public:


	void			setVelocity(D3DXVECTOR2 _velocity) { m_Velocity = _velocity; }
	void			setVelocityX(float _x) { m_Velocity.x = _x; }
	void			setVelocityY(float _y) { m_Velocity.y = _y; }
	D3DXVECTOR2		getVelocity() { return m_Velocity; }

	void			setAccelerate(D3DXVECTOR2 _accelerate) { m_Accelerate = _accelerate; }
	void			setAccelerateX(float _x) { m_Accelerate.x = _x; }
	void			setAccelerateY(float _y) { m_Accelerate.y = _y; }

	D3DXVECTOR2		getAccelerate() { return m_Accelerate; }

	void			setDirection(eDirection _direction) { m_Direction = _direction; }
	eDirection		getDirection() { return m_Direction; }

	CPhysicDx9();
	void SetMovementRange(int maxTop, int maxLeft, int maxRight, int maxBottom)
	{
		if (m_MovementRange == 0)
		{
			m_MovementRange = new RECT();
		}
		m_MovementRange->top = maxTop;
		m_MovementRange->left = maxLeft;
		m_MovementRange->right = maxRight;
		m_MovementRange->bottom = maxBottom;
	}

	bool CheckMovementRangeWidth(D3DXVECTOR3* _position);
	bool CheckMovementRangeHeight(D3DXVECTOR3* _position);

	void UpdateMovement(D3DXVECTOR3* _position);
	void CheckCollision(CObjectDx9* _object);
	~CPhysicDx9();
};

#endif
