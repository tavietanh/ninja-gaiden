#ifndef NINJA_SPRITE
#define NINJA_SPRITE
#include "SpriteManager.h"
#include "EObjectState.h"
class NinjaSpirte
{
	int m_inversePositionY;

	bool	m_isJump;
	bool	m_isLieDown;
	bool	m_isMove;
	bool	m_isFall;
	CSpriteDx9* m_Ninja;
	CSpriteDx9* m_Run;
	CSpriteDx9* m_Jump;
	CSpriteDx9* m_Hit;
	CSpriteDx9* m_Sit;
	CSpriteDx9* m_Sit_Hit;
	CSpriteDx9* m_Jump_Hit;
	CSpriteDx9* m_Climb;
	CSpriteDx9* m_Idle;
	CSpriteDx9* m_Skill;
	D3DXVECTOR2 m_frameSize;
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_tempPosition;
	eObjectState m_previousState;
public:
	NinjaSpirte(void);
	void UpdateAnimation(eObjectState _objectState);
	void Reset();
	void SetIsJump(bool _jump) { m_isJump = _jump; }
	void resetInverseVariable();
	D3DXVECTOR2 GetFrameSize() { return m_frameSize; }
	void Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ESpriteEffect effect, float rotateAngle, float scale, float deep, D3DXCOLOR color = 0xFFFFFFFF);
	virtual ~NinjaSpirte(void);
};
#endif
