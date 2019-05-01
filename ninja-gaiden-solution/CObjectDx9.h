#ifndef OBJECT_H
#define OBJECT_H

#include "CSpriteDx9.h"
#include "EDirection.h"

class CObjectDx9
{
protected:
	eDirection		m_Direction;
	CSpriteDx9*		m_Sprite;	
	static int		m_identifyNumber;
	int				m_ObjectIdentifyNumber;
	D3DXVECTOR3		m_Position;
public:
	CObjectDx9();
	CObjectDx9(D3DXVECTOR3 _position,eDirection _direction);
	CSpriteDx9*		getSprite() const { return m_Sprite; }

	int				getIdentifyNumber() { return this->m_identifyNumber; }

	void			setPosition(D3DXVECTOR3 _position) { m_Position = _position; }
	void			setPositionX(float _X) { m_Position.x = _X; }
	void			setPositionY(float _Y) { m_Position.y = _Y; }
	void			setPositionZ(float _Z) { m_Position.z = _Z; }
	D3DXVECTOR3		getPositionVec3() { return m_Position; }
	D3DXVECTOR2		getPositionVec2() { return D3DXVECTOR2(m_Position.x, m_Position.y); }



	virtual RECT getBound();

	virtual ~CObjectDx9();
};
#endif
