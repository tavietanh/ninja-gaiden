#ifndef CGAMESCENE_H
#define CGAMESCENE_H

#include "CGameTimeDx9.h"
#include "EIDSceneGame.h"
#include "CInputDx9.h"
#include "SceneManagerDx9.h"
#include "FrameworkDefine.h"
class SceneManagerDx9;

class GameScene
{
protected:
	eIDSceneGame eID;
public:
	GameScene(eIDSceneGame ID) { eID = ID; }
	virtual void HandleInput() = 0;
	virtual void InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice) = 0;
	virtual void Pause() = 0;
	virtual void Release() = 0;
	virtual void Render(LPD3DXSPRITE _lpDSpriteHandle) = 0;
	virtual void Resume() = 0;
	virtual void Update() = 0;
	virtual ~GameScene() {}
};
#endif