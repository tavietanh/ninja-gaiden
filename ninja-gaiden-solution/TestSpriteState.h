#ifndef TEST_SPRITE_STATE_H
#define TEST_SPRITE_STATE_H

#include "CSpriteDx9.h"
#include "GameScene.h"
#include "SpriteManager.h"
#include "SceneManagerDx9.h"
#include "Ninja.h"

#define CENTERX 400
#define CENTERY 300

class TestSpriteState : public GameScene
{
private:
	Ninja*		m_Ninja;
	CSpriteDx9* testSprite;
public:
	TestSpriteState(eIDSceneGame ID) : GameScene(ID) {}
	~TestSpriteState() {}
	void InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice);
	void HandleInput();
	void Update();
	void Render(SPRITEHANDLE _lpDSpriteHandle);
	void RenderMap(SPRITEHANDLE _lpDSpriteHandle);
	void Pause();
	void Resume();
	void Release();
};

#endif