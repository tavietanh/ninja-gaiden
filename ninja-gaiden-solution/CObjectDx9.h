#ifndef OBJECT_H
#define OBJECT_H

#include "EObjectState.h"
#include "EObjectID.h"
#include "CSpriteDx9.h"
#include "ETypeObject.h"
#include "CPhysicDx9.h"
#include "EDirection.h"
#include "IDDirection.h"
#include "SpriteManager.h"
#include "SoundMangerDx9.h"
#include "Box.h"

class CObjectDx9
{
protected:
	eObjectID		m_eObjectID;
	eDirection		m_Direction;
	CSpriteDx9*		m_Sprite;
	eObjectState	m_ObjectState;
	ETypeObject		m_TypeObject;
	int				m_TimeChangeState;
	int				m_TimeChangeDirectAttack;
	int				m_AttackCounter;
	static int		m_identifyNumber;
	int				m_ObjectIdentifyNumber;
	D3DXVECTOR3		m_Position;
	D3DXVECTOR3		m_SPosition;
public:
	CObjectDx9();
	CObjectDx9(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	CSpriteDx9*		getSprite() const { return m_Sprite; }

	int				getIdentifyNumber() { return this->m_identifyNumber; }

	void			setPosition(D3DXVECTOR3 _position) { m_Position = _position; }
	void			setPositionX(float _X) { m_Position.x = _X; }
	void			setPositionY(float _Y) { m_Position.y = _Y; }
	void			setPositionZ(float _Z) { m_Position.z = _Z; }
	
	D3DXVECTOR3		getPositionVec3() { return m_Position; }
	D3DXVECTOR2		getPositionVec2() { return D3DXVECTOR2(m_Position.x, m_Position.y); }


	eObjectID		getID() const { return m_eObjectID; }
	ETypeObject		getTypeObject() const { return m_TypeObject; }

	eObjectState	getObjectState() const { return m_ObjectState; }
	void			setObjectState(eObjectState _state) { this->m_ObjectState = _state; };

	eDirection		getDirection() const { return this->m_Direction; };
	virtual RECT getBound();
	void reset();
	virtual void Initialize() = 0;
	virtual void UpdateAnimation() = 0;

	virtual void UpdateCollision(CObjectDx9* checkingObject) = 0;
	virtual void Update() = 0;
	virtual void Render(SPRITEHANDLE spriteHandle) = 0;
	virtual void Release() = 0;

	virtual ~CObjectDx9();
};
#endif
