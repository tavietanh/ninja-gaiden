#ifndef PLAY_SCENE_H
#define PLAY_SCENE_H

#include "GameScene.h"
#include "SceneManagerDx9.h"
#include "CSpriteDx9.h"
#include "SpriteManager.h"
#include "CCamera.h"
#include "Tile.h"
#include "EnemyRun.h"
#include "Markup.h"
#include "Ninja.h"
#include "VirtualObject.h"
#include <list>
#include "Grid.h"
#include "SoundMangerDx9.h"
#include "background.h"
#include "MenuScene.h"
#include "GameOverScene.h"

#define CENTERX 400
#define CENTERY 300

class PlayScene : public GameScene
{
private:
	Ninja*		m_Ninja;
	Grid*		m_Grid;
	int			map;
	CSpriteDx9* testSprite;
	SoundBuffer*		m_SoundBackGround;
	background	m_background;
	int m_timefreeze;
	bool isDead;
	int m_timer;
public:
	PlayScene(eIDSceneGame ID, int _map) : GameScene(ID) { map = _map; }
	~PlayScene() {}
	void InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice);
	void HandleInput();
	void Update();
	void Render(SPRITEHANDLE _lpDSpriteHandle);
	void Pause();
	void Resume();
	void Release();
};

#endif