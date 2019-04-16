#ifndef CSCENEMANAGERDX9_H
#define CSCENEMANAGERDX9_H

#include "CGameTimeDx9.h"
#include "CInputDx9.h"
#include "FrameworkDefine.h"
#include <vector>
#include "GameScene.h"
using namespace std;
class GameScene;

class SceneManagerDx9
{
private:

	SceneManagerDx9() {}

	~SceneManagerDx9() {}

	vector<GameScene*> m_ListGameScene;

	static SceneManagerDx9* s_Instance;

	LPDIRECT3DDEVICE9		m_lpDirectDevice;

public:

	static SceneManagerDx9* getInstance();

	void setDirectDevice(const LPDIRECT3DDEVICE9& lpDirectDevice);

	void Initialize();

	void HandleInput();

	void Update();

	void Render(LPD3DXSPRITE _lpDSpriteHandle);

	void AddElement(GameScene* GameScene);

	void ExitState();

	void ReplaceBy(GameScene* GameScene);

	void ClearAll();
};
#endif