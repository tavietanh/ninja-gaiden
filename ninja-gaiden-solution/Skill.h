#ifndef __SKILL_H__
#define __SKILL_H__

#include "DynamicObject.h"
#include "EIDTypeSkill.h"
#include "EDirectAttack.h"
#include "EIDItem.h"
#include "CCamera.h"

class Skill : public DynamicObject
{
protected:
	eIDTypeSkill m_TypeSkill;
	D3DXVECTOR3 m_StartPosition;
	float m_livingTime;
	float m_factor;
public:
	eIDTypeSkill getTypeSkill() const { return m_TypeSkill; };
	void setTypeSkill(eIDTypeSkill _typeSkill) { this->m_TypeSkill = _typeSkill; };
	void setDirectAttack(eDirectAttack _directAttack) { this->m_DirectAttack = _directAttack; };
	void setStartPosition(D3DXVECTOR3 _position) { this->m_StartPosition = _position; };
	void setFactor(float _factor) { this->m_factor = _factor; };

	float getLivingTime() { return m_livingTime; };
	void ResetLivingTime();
	Skill();
	Skill(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	virtual ~Skill();
	virtual void Initialize() = 0;
	virtual void reset();
	void Release();
	void Render(SPRITEHANDLE spriteHanlde);
	void Update();
	void UpdateAnimation();
	void UpdateCollision(CObjectDx9* checkingObject);
	virtual void UpdateMovement() = 0;
};

#endif

