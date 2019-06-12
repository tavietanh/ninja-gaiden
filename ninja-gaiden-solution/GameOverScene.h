#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "GameScene.h"
#include "SpriteManager.h"
#include "SceneManagerDx9.h"
#include "SoundMangerDx9.h"
#include "MenuScene.h"

class GameOverScene : public GameScene
{
private:
	bool m_IsDone;
	CSpriteDx9*			m_gameover;
	int m_color;
public:
	GameOverScene(eIDSceneGame ID) : GameScene(ID) {}
	~GameOverScene() {}
	void InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice);
	void HandleInput();
	void Update();
	void Render(LPD3DXSPRITE _lpDSpriteHandle);
	void Pause();
	void Resume();
	void Release();
};
#endif