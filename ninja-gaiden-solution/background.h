#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "SpriteManager.h"

class background
{
private:
	CSpriteDx9* sprite_background;
	CSpriteDx9* sprite_health_full;
	CSpriteDx9* sprite_health_empty;
	CSpriteDx9* sprite_score;
public:
	background();
	~background();
	void Initialize();
	void UpdateAnimation();
	void Render(SPRITEHANDLE spriteHandle);
	void RenderHealthNinja(SPRITEHANDLE spriteHandle,float x,float y);
	void RenderHealthBoss(SPRITEHANDLE spriteHandle, float x, float y);
	void RenderItem(SPRITEHANDLE spriteHandle, float x, float y);
	void RenderScore(SPRITEHANDLE spriteHandle, float x, float y);
	void Release();
};

#endif

