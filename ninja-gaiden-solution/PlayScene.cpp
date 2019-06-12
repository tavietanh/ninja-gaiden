#include "PlayScene.h"

void PlayScene::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	m_Grid = new Grid();
	m_Ninja = new Ninja(D3DXVECTOR3(50,80 , 1), eDirection::RIGHT, eObjectID::NINJA);
	isDead = false;
	Camera::getInstance()->Reset();
	string mapPath = "resources\\Map\\" + to_string(map) + "\\" + to_string(map) + ".xml";
	SkillManager::getInstance()->Initialize();
	m_Grid->BuildGrid(mapPath.c_str(), (eSpriteID)(map));
	Camera::getInstance()->setMaxWidth(CGlobal::MapWidth);
	m_timer = 150;
	CGlobal::healthNinja = 16;
	CGlobal::timer = 150;
	CGlobal::skills = 50;
	CGlobal::life = 1;
	CGlobal::healthBoss = 16;
	switch (map)
	{
	case 1:
		this->m_SoundBackGround = SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_BACKGROUND_1);
		break;
	case 2:
		this->m_SoundBackGround = SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_BACKGROUND_2);
		break;
	case 3:
		this->m_SoundBackGround = SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_BACKGROUND_3);
		break;
	default:
		break;
	}
	m_SoundBackGround->Repeat();
	m_background.Initialize();
}

float scalexxx = 1.0f;

void PlayScene::HandleInput()
{
	m_Ninja->HandleInput();
}

void PlayScene::Update()
{
	m_timer += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	if (m_timer > 2000)
	{
		CGlobal::timer -= 1;
		m_timer = 0;
	}
	if (CGlobal::healthNinja == 0 || CGlobal::timer==0)
	{
		CGlobal::timer = 150;
		m_SoundBackGround->Stop();
		if (isDead==false)
		{
			CGlobal::life -= 1;
			SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::SOUND_DEAD)->Play();
			isDead = true;
		}
		m_timefreeze += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_timefreeze > 8000)
		{
			if (CGlobal::life <= 0)
			{
				SceneManagerDx9::getInstance()->ReplaceBy(new GameOverScene(eIDSceneGame::GAMEOVER));
			}
			else {
				SceneManagerDx9::getInstance()->ReplaceBy(new PlayScene(eIDSceneGame::PLAY, map));
				m_Ninja->setPosition(D3DXVECTOR3(50, 80, 1));
				CGlobal::healthNinja = 16;
				m_timefreeze = 0;
				isDead = false;
			}
			
		}
	}
	if (m_Ninja->getPositionVec2().x > CGlobal::MapWidth-20 && map == 1)
	{
		m_SoundBackGround->Stop();
		SceneManagerDx9::getInstance()->ReplaceBy(new PlayScene(eIDSceneGame::PLAY, 2));
		m_Ninja->setPosition(D3DXVECTOR3(50, 80, 1));
	}
	if (m_Ninja->getPositionVec2().x > CGlobal::MapWidth - 50 && map == 2)
	{
		m_SoundBackGround->Stop();
		SceneManagerDx9::getInstance()->ReplaceBy(new PlayScene(eIDSceneGame::PLAY, 3));
		m_Ninja->setPosition(D3DXVECTOR3(50, 80, 1));
	}
	Camera::getInstance()->UpdateCamera(&m_Ninja->getPositionVec3());
	
	m_Ninja->UpdateAnimation();
	m_Ninja->UpdateMovement();
	m_Ninja->SetFlag();
	m_Grid->InsertObjectIntoView(Camera::getInstance()->getBound(), m_Grid->m_cells);
	SkillManager::getInstance()->Update();
	SkillManager::getInstance()->UpdateMovement();
	SkillManager::getInstance()->UpdateAnimation();
	m_Grid->Update();
	m_Grid->UpdateAnimation();
	if (m_Ninja->getItemNinja() != eIDItem::ITEM_FREEZE)
	{
		m_Grid->UpdateMovement();
	}
	else 
	{
		m_timefreeze += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_timefreeze > 5000)
		{
			m_Ninja->setItemNinja(eIDItem::ITEM_5_POWER);
			m_timefreeze = 0;
		}
	}
	for (int i = 0; i < (int)m_Grid->mListObjectCollisionInView.size(); ++i)
	{
		m_Ninja->UpdateCollision(m_Grid->mMapObjectCollisionInGame[m_Grid->mListObjectCollisionInView[i]]);
		m_Grid->UpdateCollision(m_Grid->mMapObjectCollisionInGame[m_Grid->mListObjectCollisionInView[i]]);
		ItemManager::getInstance()->UpdateCollision(m_Grid->mMapObjectCollisionInGame[m_Grid->mListObjectCollisionInView[i]]);
	}
	m_Grid->UpdateCollision(m_Ninja);

	for (std::list<Skill*>::iterator i = SkillManager::getInstance()->m_ListSkillInGame.begin(); i != SkillManager::getInstance()->m_ListSkillInGame.end(); ++i)
	{
		for (std::list<Skill*>::iterator j = SkillManager::getInstance()->m_ListSkillInGame.begin(); j != SkillManager::getInstance()->m_ListSkillInGame.end(); ++j)
		{
			(*i)->UpdateCollision(*j);
		}
		m_Grid->UpdateCollision(*i);
		m_Ninja->UpdateCollision(*i);
	}
	ItemManager::getInstance()->Update();
	ItemManager::getInstance()->UpdateCollision(m_Ninja);
}
void PlayScene::Render(SPRITEHANDLE _lpDSpriteHandle)
{
	m_background.Render(_lpDSpriteHandle);
	m_Grid->Render(_lpDSpriteHandle);
	m_Ninja->Render(_lpDSpriteHandle);
	ItemManager::getInstance()->Render(_lpDSpriteHandle);
	SkillManager::getInstance()->Render(_lpDSpriteHandle);
}

void PlayScene::Pause()
{

}

void PlayScene::Resume()
{

}

void PlayScene::Release()
{
	
}
