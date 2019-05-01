#ifndef NINJA_SPRITE
#define NINJA_SPRITE
#include "SpriteManager.h"
class NinjaSpirte
{
	int m_inversePositionY;
	bool	m_isMove;
	CSpriteDx9* m_Run;
	D3DXVECTOR2 m_frameSize;
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_tempPosition;
public:
	NinjaSpirte(void);
	void saveCurrentState();
	void loadCurrentState();
	void UpdateAnimation();
	void resetInverseVariable();
	D3DXVECTOR2 GetFrameSize() { return m_frameSize; }
	void Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ESpriteEffect effect, float rotateAngle, float scale, float deep, D3DXCOLOR color = 0xFFFFFFFF);
	~NinjaSpirte();
};
#endif
