#include "SpriteManager.h"

SpriteManager* SpriteManager::s_Instance = 0;

SpriteManager::SpriteManager(void)
{

}

SpriteManager* SpriteManager::getInstance()
{
	if (s_Instance == 0)
	{
		s_Instance = new SpriteManager();
	}
	return s_Instance;
}

void SpriteManager::LoadSpriteContent(LPDIRECT3DDEVICE9 _lpDirectDevice, const char* fileName, eSpriteID eID, int Column, int Row, int TotalFrame)
{
	CSpriteDx9* sprite = new CSpriteDx9();
	sprite->LoadContent(_lpDirectDevice, fileName, Column, Row, TotalFrame);
	m_ListSprite[eID] = sprite;
}

CSpriteDx9* SpriteManager::getSprite(eSpriteID eID)
{
	map<eSpriteID, CSpriteDx9*>::iterator i;

	i = m_ListSprite.find(eID);

	if (i == m_ListSprite.end())
		return 0;

	return i->second;
}

void SpriteManager::InitializeListSprite(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	LoadSpriteContent(_lpDirectDevice, "resources\\Map\\1\\1.png", eSpriteID::SPRITE_MAP_1, 79, 1, 79);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Ninja\\ninja_run.png", eSpriteID::SPRITE_NINJA_RUN, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Ninja\\ninja_hit.png", eSpriteID::SPRITE_NINJA_HIT, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Ninja\\ninja_jump.png", eSpriteID::SPRITE_NINJA_JUMP, 4, 1, 4);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Ninja\\ninja_idle.png", eSpriteID::SPRITE_NINJA_IDLE, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Ninja\\ninja_sit.png", eSpriteID::SPRITE_NINJA_SIT, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Ninja\\ninja_jump_hit.png", eSpriteID::SPRITE_NINJA_JUMP_HIT, 4, 1, 4);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Ninja\\ninja_sit_hit.png", eSpriteID::SPRITE_NINJA_SIT_HIT, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Ninja\\ninja_skill.png", eSpriteID::SPRITE_NINJA_SKILL, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Ninja\\ninja_climb.png", eSpriteID::SPRITE_NINJA_CLIMB, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\EnemyRun\\enemy_run.png", eSpriteID::SPRITE_ENEMY_RUN, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\EnemySword\\enemy_sword.png", eSpriteID::SPRITE_ENEMY_SWORD, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\explosion.png", eSpriteID::SPRITE_EXPLOSION, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\GifBird\\GifBird.png", eSpriteID::SPRITE_GIF_BIRD, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\GifButerfly\\GifButerfly.png", eSpriteID::SPRITE_GIF_BUTERFLY, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\ThrowStar.png", eSpriteID::SPRITE_THROW_STAR, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\Skill\\SkillThrowStar.png", eSpriteID::SPRITE_SKILL_THROW_STAR, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\Flames.png", eSpriteID::SPRITE_FLAMES, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\Skill\\SkillFlames.png", eSpriteID::SPRITE_SKILL_FLAMES, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\WindmilStar.png", eSpriteID::SPRITE_WINDMIL_STAR, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\Skill\\SkillWindmilStar.png", eSpriteID::SPRITE_SKILL_WINDMIL_STAR, 2, 1, 2);
}

void SpriteManager::Release()
{
	map<eSpriteID, CSpriteDx9*>::iterator i;
	for (i = m_ListSprite.begin(); i != m_ListSprite.end(); i++)
	{
		i->second->Release();
		SAFE_DELETE(i->second);
	}
	m_ListSprite.clear();
}

SpriteManager::~SpriteManager(void)
{
}

