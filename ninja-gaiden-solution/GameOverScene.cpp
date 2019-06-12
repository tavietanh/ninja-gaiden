#include "GameOverScene.h"



void GameOverScene::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	m_gameover = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_MENU_GAME_OVER));
	m_IsDone = false;
}
void GameOverScene::HandleInput()
{
	if (m_IsDone == true)
	{
		if (CInputDx9::getInstance()->IsKeyPress(DIK_RETURN))
		{
			SceneManagerDx9::getInstance()->ReplaceBy(new MenuScene(eIDSceneGame::MENU));
		}
	}
}
void GameOverScene::Update()
{
	Camera::getInstance()->Reset();
	m_color += 1;
	if (m_color >= 255)
	{
		m_IsDone = true;
		m_color = 255;
	}

}

void GameOverScene::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	D3DXCOLOR color;
	color = D3DCOLOR_ARGB(m_color, 0xff, 0xff, 0xff);
	m_gameover->Render(_lpDSpriteHandle, D3DXVECTOR2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), ESpriteEffect::None, 0.0f, 1.0f, 1.0f, color);
}

void GameOverScene::Pause()
{
}

void GameOverScene::Resume()
{
}

void GameOverScene::Release()
{
}

