#include "NinjaSpirte.h"



NinjaSpirte::NinjaSpirte(void)
{
	m_Run = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_NINJA_RUN));
	resetInverseVariable();
}
void NinjaSpirte::resetInverseVariable()
{
	m_inversePositionY = -1;
}
void NinjaSpirte::saveCurrentState()
{
	m_tempPosition = m_Position;
}
void NinjaSpirte::loadCurrentState()
{
	m_Position = m_tempPosition;
}
void NinjaSpirte::UpdateAnimation() 
{
	m_Position = D3DXVECTOR3(0, 0, 0);
	m_frameSize = D3DXVECTOR2(27, 31);
	resetInverseVariable();
	m_Run->UpdateAnimation(250);
}
void NinjaSpirte::Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ESpriteEffect effect, float rotateAngle, float scale, float deep, D3DXCOLOR color)
{
	m_Run->Render(spriteHandle, D3DXVECTOR2(position.x, position.y), effect, rotateAngle, scale, deep, color);
}

NinjaSpirte::~NinjaSpirte()
{
}
