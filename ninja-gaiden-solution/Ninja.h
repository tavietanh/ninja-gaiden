#ifndef NINJA_H
#define NINJA_H
#include "DynamicObject.h"
#include "CInputDx9.h"
#include "NinjaSpirte.h"
#include "EDirection.h"
#include "CGlobal.h"
#include <fstream>
#include <list>

using namespace std;
class Ninja : public DynamicObject
{
	NinjaSpirte* m_NinjaSprite;
	bool HandleInputShooting();
	bool isAddBullet();
	bool isFall;
	bool isJump;
	bool isLieDown;
	bool isSetVelocityDeathState;
	bool isInvulnerable;
	unsigned char m_colorAlpha;
	int m_inverseColorAlpha;
	float m_maxPositionY;
	float m_timeAddBullet;
	float m_timeHit;
	float m_timeClimb;
	float m_timeDeath;
	float m_timeDelayRunAndShootRun;
	float m_timeWaterBomb;
	float m_timeBeforeDeadBottom;
	int m_timeInvulnerable;

	int UpdateInvulnerableAnimation();
	int HandleInputAimBottomRightState();
	int HandleInputAimTopRightState();
	int HandleInputAimUpState();
	int HandleInputBeforeDieState();
	int HandleInputClimbState();
	int HandleInputDeadState();
	int HandleInputDiveState();
	int HandleInputIdleState();
	int HandleInputJumpState();
	int HandleInputSitState();
	int HandleInputSitHitState();
	int HandleInputRunState();
	int HandleInputHitState();
	int HandleInputSwimShootState();
	int HandleInputSwimShootTopRightState();
	int HandleInputSwimShootUpState();
	int HandleInputSwimState();
	int HandleInputWaterBombState();
	int m_life;
	list<CObjectDx9*> m_objectBelowCurrent;
	list<CObjectDx9*> m_objectBelowPrevious;
	CObjectDx9* m_ignoreCollisionObject;
	RECT m_RectangleCheckingObjectBelow;

	float prePosX;
	float finalPosX;

	void SetFallFlag();
	void SetVelocityXZero();
	void SetVelocityYZero();
public:
	Ninja();
	Ninja(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	int getNinjaLife() { return m_life; }
	void setNinjaLife(int _life) { m_life = _life; }
	int UpdateCollisionTileBase(IDDirection collideDirection, CObjectDx9* checkingObject);
	RECT getBound();
	void Initialize();
	void SetFlag();
	void setRectangleCheckingObjectBelow();
	void Release();
	void Render(SPRITEHANDLE spriteHandle);
	void HandleInput();
	void Update();
	void UpdateCollision(CObjectDx9* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void UpdatePreviousIgnoreList();
	void CleanIgnoreList();
	virtual ~Ninja();
};
#endif
