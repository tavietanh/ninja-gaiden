#include "background.h"
#include "CCamera.h"
#include "CGlobal.h"

background::background()
{

}

void background::Initialize()
{
	sprite_background = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BACKGROUND));
	sprite_health_full = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_HEALTH_BAR_FULL));
	sprite_health_empty = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_HEALTH_BAR_EMPTY));
	sprite_score = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_NUMBER));
}

void background::UpdateAnimation()
{
	sprite_background->UpdateAnimation(350);
}


void background::Render(SPRITEHANDLE _spriteHandler)
{
	sprite_background->RenderWithoutTransform(_spriteHandler, D3DXVECTOR2(SCREEN_WIDTH/2, 200), ESpriteEffect::None, 0.0f, 1.0f, 1.0f);
	RenderHealthBoss(_spriteHandler,173,192);
	RenderHealthNinja(_spriteHandler,173, 200);
	RenderItem(_spriteHandler, 106, 196);
	RenderScore(_spriteHandler, 108, 207);
}

void background::Release()
{
	this->sprite_background->Release();
	this->sprite_background = 0;
}
void background::RenderHealthBoss(SPRITEHANDLE _spriteHandler,float x,float y)
{
	for (int i = 0; i < 16; i++)
	{
		if (i < CGlobal::healthBoss)
		{
			SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_HEALTH_BAR_FULL)->RenderWithoutTransform(
				_spriteHandler,
				D3DXVECTOR2((float)(4*i)+x, y),
				ESpriteEffect::None,
				0.0f,
				1.0f,
				1.0f);
		}
		else
		{
			SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_HEALTH_BAR_EMPTY)->RenderWithoutTransform(
				_spriteHandler,
				D3DXVECTOR2((float)(4 * i) +x, y),
				ESpriteEffect::None,
				0.0f,
				1.0f,
				1.0f);
		}
	}
}
void background::RenderHealthNinja(SPRITEHANDLE _spriteHandler, float x, float y)
{
	for (int i = 0; i < 16; i++)
	{
		if (i < CGlobal::healthNinja)
		{
			SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_HEALTH_BAR_FULL)->RenderWithoutTransform(
				_spriteHandler,
				D3DXVECTOR2((float)(4 * i) + x, y),
				ESpriteEffect::None,
				0.0f,
				1.0f,
				1.0f);
		}
		else
		{
			SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_HEALTH_BAR_EMPTY)->RenderWithoutTransform(
				_spriteHandler,
				D3DXVECTOR2((float)(4 * i) + x, y),
				ESpriteEffect::None,
				0.0f,
				1.0f,
				1.0f);
		}
	}
}
void background::RenderItem(SPRITEHANDLE _spriteHandler, float x, float y)
{
	switch (CGlobal::Item)
	{
	case SKILL_FLAMES:
		SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_FLAMES)->RenderWithoutTransform(
			_spriteHandler,
			D3DXVECTOR2(x, y),
			ESpriteEffect::None,
			0.0f,
			1.0f,
			1.0f);
		break;
	case SKILL_THROW_STAR:
		SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_THROW_STAR)->RenderWithoutTransform(
			_spriteHandler,
			D3DXVECTOR2(x, y),
			ESpriteEffect::None,
			0.0f,
			1.0f,
			1.0f);
		break;
	case SKILL_WINDMIL_STAR:
		SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_WINDMIL_STAR)->RenderWithoutTransform(
			_spriteHandler,
			D3DXVECTOR2(x, y),
			ESpriteEffect::None,
			0.0f,
			1.0f,
			1.0f);
		break;
	default:
		break;
	}
}
void background::RenderScore(SPRITEHANDLE _spriteHandler, float x, float y)
{
	int a = CGlobal::score;
	for (int i = 0; i < 6; i++)
	{
		int b = a % 10;
		a = a / 10;
		CSpriteDx9* temp = sprite_score;
		temp->getAnimation()->setSourceRectAtIndex(b);
		temp->RenderWithoutTransform(
			_spriteHandler,
			D3DXVECTOR2(x - (float)(8 * i), y),
			ESpriteEffect::None,
			0.0f,
			1.0f,
			1.0f);

	}
}
background::~background()
{

}
