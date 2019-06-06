#ifndef NINJA_H
#define NINJA_H
#include "DynamicObject.h"
#include "CInputDx9.h"
#include "NinjaSpirte.h"
#include "EDirection.h"
#include "CGlobal.h"
#include "Skill.h"
#include "SkillPool.h"
#include "SkillManager.h"
#include <fstream>
#include <list>
using namespace std;
class Ninja : public DynamicObject
{
	NinjaSpirte* m_NinjaSprite;
	bool isFall;
	bool isJump;
	bool isClimb;
	bool isSetVelocityDeathState;
	bool isInvulnerable;
	unsigned char m_colorAlpha;
	int m_inverseColorAlpha;
	float m_maxPositionY;
	float m_timeHit;
	float m_timeClimb;
	float m_timeDeath;
	float m_timeBeforeDeadBottom;
	int m_timeInvulnerable;
	int maxClimb;
	int minClimb;
	D3DXVECTOR3 GetStartPositionOfSkill(float x,float y);
	eIDSkillNinja m_SkillNinja;
	eIDSkillNinja m_ItemNinja;
	int UpdateInvulnerableAnimation();
	int HandleInputSkilling();
	int HandleInputHangState();
	int HandleInputClimbState();
	int HandleInputDeadState();
	int HandleInputSkillState();
	int HandleInputIdleState();
	int HandleInputJumpState();
	int HandleInputSitState();
	int HandleInputSitHitState();
	int HandleInputRunState();
	int HandleInputHitState();
	int m_life;
	list<CObjectDx9*> m_objectBelowCurrent;
	list<CObjectDx9*> m_objectBelowPrevious;
	CObjectDx9* m_ignoreCollisionObject;
	RECT m_RectangleCheckingObjectBelow;

	float prePosX;
	float finalPosX;

	int CheckOutBottomCamera();
	void SetFallFlag();
	void SetVelocityXZero();
	void SetVelocityYZero();
public:
	Ninja();
	Ninja(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	int getNinjaLife() { return m_life; }
	void setNinjaLife(int _life) { m_life = _life; }
	void SetInvulnerable(bool para) { this->isInvulnerable = para; };
	int UpdateCollisionTileBase(IDDirection collideDirection, CObjectDx9* checkingObject);
	RECT getBound();
	void UseSkill();
	void Initialize();
	void SetFlag();
	void setSkillNinja(eIDSkillNinja _skillNinja) { this->m_SkillNinja = _skillNinja; };
	void setItemNinja(eIDSkillNinja _itemNinja) { this->m_ItemNinja = _itemNinja; };
	void setRectangleCheckingObjectBelow();
	void Release();
	void Render(SPRITEHANDLE spriteHandle);
	void HandleInput();
	void Update();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	virtual ~Ninja();
};
#endif
