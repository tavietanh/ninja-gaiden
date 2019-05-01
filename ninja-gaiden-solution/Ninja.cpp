#include "Ninja.h"



Ninja::Ninja()
{
}
Ninja::Ninja(D3DXVECTOR3 _position, eDirection _direction)
	: DynamicObject(_position, _direction)
{
	m_NinjaSprite = new NinjaSpirte();
	m_Position.z = 1.0f;
	prePosX = 0;
	finalPosX = 0;
}
void Ninja::UpdateAnimation()
{
	m_NinjaSprite->UpdateAnimation();
}
void Ninja::UpdateMovement()
{
	CGlobal::Ninja_X = (int)(getPositionVec2().x);
	CGlobal::Ninja_Y = (int)(getPositionVec2().y);
}
void Ninja::HandleInput()
{
	if (CInputDx9::getInstance()->IsKeyPress(DIK_RIGHT))
	{
		m_Position.x += 20;
	}
}
void Ninja::Render(SPRITEHANDLE spriteHandle)
{
	D3DXCOLOR color = D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff);
	if (m_Direction == eDirection::RIGHT)
	{
		m_NinjaSprite->Render(spriteHandle,
			getPositionVec2(),
			ESpriteEffect::None,
			0.0f,
			1.0f,
			1.0f,
			color);
		return;
	}
	if (m_Direction == eDirection::LEFT)
	{
		m_NinjaSprite->Render(spriteHandle,
			getPositionVec2(),
			ESpriteEffect::Horizontally,
			0.0f,
			1.0f,
			1.0f,
			color);
		return;
	}
}

Ninja::~Ninja()
{
}
