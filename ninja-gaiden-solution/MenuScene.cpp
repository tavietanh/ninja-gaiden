#include "MenuScene.h"



void MenuScene::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	m_tecmo = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_MENU_TECMO));
	m_present = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_MENU_PRESENT));
	m_ninja = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPIRTE_MENU_NINJA));
	m_tecmoPosition.x = (float)(SCREEN_WIDTH / 2);
	m_ninjaPosition.x = (float)(SCREEN_WIDTH / 2-50);
	//m_MenuPosition.x = 0;
	m_ninjaPosition.y = SCREEN_HEIGHT / 2;
	m_tecmoPosition.y = SCREEN_HEIGHT / 2+8;
	m_tecmoPosition.z = 0;
	m_presentPosition.x = (float)(SCREEN_WIDTH / 2);
	m_presentPosition.y = SCREEN_HEIGHT / 2-15;
	m_presentPosition.z = 1;
	m_color = 0;
	m_Ispresent = false;
	m_IsDone = false;
	m_playsound = false;
}
void MenuScene::HandleInput()
{
	if (m_IsDone == true)
	{
		if (CInputDx9::getInstance()->IsKeyPress(DIK_RETURN))
		{
			SceneManagerDx9::getInstance()->ReplaceBy(new PlayScene(eIDSceneGame::PLAY, 1));
		}
	}
}
void MenuScene::Update()
{
	Camera::getInstance()->Reset();
	if (m_color > 255)
	{
		m_color -= 1;
	}
	else m_color += 1;
	if (m_color >= 255)
	{
		if (m_color == 255)
		{
			m_color = 510;
		}
		if (m_color == 256)
		{
			m_Ispresent = true;
			m_color = 0;
		}
		if (m_Ispresent == true)
		{
			m_color = 255;
			m_ninjaPosition.y += 0.3f;
			if (m_ninjaPosition.y >= 165) m_ninjaPosition.y = 165;
			m_tecmoPosition.y -= 0.5f;
			if (m_tecmoPosition.y <= 30)
			{
				m_tecmoPosition.y = 30;
				if (m_playsound == false)
				{
					m_IsDone = true;
					m_playsound = true;
					SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_LOGO)->Play();
				}
			}
		}
	}
		
}

void MenuScene::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	D3DXCOLOR color;
	color = D3DCOLOR_ARGB(m_color, 0xff, 0xff, 0xff);
	if (m_color >= 255)
	{
		m_tecmo->Render(_lpDSpriteHandle, D3DXVECTOR2(m_tecmoPosition.x, m_tecmoPosition.y), ESpriteEffect::None, 0.0f, 1.0f, m_tecmoPosition.z);
	}
	else m_tecmo->Render(_lpDSpriteHandle, D3DXVECTOR2(m_tecmoPosition.x, m_tecmoPosition.y), ESpriteEffect::None, 0.0f, 1.0f, m_tecmoPosition.z, color);
	if(m_Ispresent==false)
		m_present->Render(_lpDSpriteHandle, D3DXVECTOR2(m_presentPosition.x, m_presentPosition.y), ESpriteEffect::None, 0.0f, 1.0f, m_presentPosition.z, color);
	else
	{
		m_tecmo->Render(_lpDSpriteHandle, D3DXVECTOR2(m_tecmoPosition.x, m_tecmoPosition.y), ESpriteEffect::None, 0.0f, 1.0f, m_tecmoPosition.z);
		m_ninja->Render(_lpDSpriteHandle, D3DXVECTOR2(m_ninjaPosition.x, m_ninjaPosition.y), ESpriteEffect::None, 0.0f, 1.0f, m_ninjaPosition.z);
	}
	if (m_tecmoPosition.y == 30)
	{
		SpriteManager::getInstance()->getSprite(eSpriteID::SPIRTE_MENU_LOGO)->Render(_lpDSpriteHandle, D3DXVECTOR2(m_ninjaPosition.x + 118, m_ninjaPosition.y), ESpriteEffect::None, 0.0f, 1.0f, m_ninjaPosition.z);
		SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_MENU_CENTER)->Render(_lpDSpriteHandle, D3DXVECTOR2(m_tecmoPosition.x, SCREEN_HEIGHT / 2-30), ESpriteEffect::None, 0.0f, 1.0f, m_tecmoPosition.z);
	}
}

void MenuScene::Pause()
{
}

void MenuScene::Resume()
{
}

void MenuScene::Release()
{
}
