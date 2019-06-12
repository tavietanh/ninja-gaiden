#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "GameScene.h"
#include "SpriteManager.h"
#include "SceneManagerDx9.h"
#include "SoundMangerDx9.h"
#include "PlayScene.h"

class MenuScene : public GameScene
{
private:
	bool m_playsound;
	bool m_IsDone;
	CSpriteDx9*			m_tecmo;
	CSpriteDx9*			m_present;
	CSpriteDx9*			m_ninja;
	D3DXVECTOR3			m_tecmoPosition;
	D3DXVECTOR3			m_ninjaPosition;
	D3DXVECTOR3			m_presentPosition;
	bool m_Ispresent;
	int m_color;
public:
	MenuScene(eIDSceneGame ID) : GameScene(ID) {}
	~MenuScene(){}
	void InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice);
	void HandleInput();
	void Update();
	void Render(LPD3DXSPRITE _lpDSpriteHandle);
	void Pause();
	void Resume();
	void Release();
};
#endif