#ifndef TEST_SPRITE_STATE_H
#define TEST_SPRITE_STATE_H

#include "GameScene.h"
#include "SceneManagerDx9.h"
#include "CSpriteDx9.h"
#include "SpriteManager.h"
#include "CCamera.h"
#include "MapReader.h"
#include "Tile.h"
#include "EnemyRun.h"
#include "Markup.h"
#include "Ninja.h"
#include "VirtualObject.h"
#include <list>
#include "Grid.h"

#define CENTERX 400
#define CENTERY 300

class TestSpriteState : public GameScene
{
private:
	Ninja*		m_Ninja;
	Grid*		m_Grid;
	int			map;
	CSpriteDx9* testSprite;
public:
	TestSpriteState(eIDSceneGame ID, int _map) : GameScene(ID) { map = _map; }
	~TestSpriteState() {}
	void InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice);
	void HandleInput();
	void Update();
	void Render(SPRITEHANDLE _lpDSpriteHandle);
	void Pause();
	void Resume();
	void Release();
};

#endif