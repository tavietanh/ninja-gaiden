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
	LoadSpriteContent(_lpDirectDevice, "resources\\Map\\2\\2.png", eSpriteID::SPRITE_MAP_2, 49, 1, 49);
	LoadSpriteContent(_lpDirectDevice, "resources\\Map\\3\\3.png", eSpriteID::SPRITE_MAP_3, 41, 1, 41);
	LoadSpriteContent(_lpDirectDevice, "resources\\Map\\background.png", eSpriteID::SPRITE_BACKGROUND, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Map\\number.png", eSpriteID::SPRITE_NUMBER, 10, 1, 10);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Ninja\\ninja_run.png", eSpriteID::SPRITE_NINJA_RUN, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Ninja\\ninja_hit.png", eSpriteID::SPRITE_NINJA_HIT, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Ninja\\ninja_jump.png", eSpriteID::SPRITE_NINJA_JUMP, 4, 1, 4);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Ninja\\ninja_idle.png", eSpriteID::SPRITE_NINJA_IDLE, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Ninja\\ninja_sit.png", eSpriteID::SPRITE_NINJA_SIT, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Ninja\\ninja_jump_hit.png", eSpriteID::SPRITE_NINJA_JUMP_HIT, 4, 1, 4);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Ninja\\ninja_sit_hit.png", eSpriteID::SPRITE_NINJA_SIT_HIT, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Ninja\\ninja_skill.png", eSpriteID::SPRITE_NINJA_SKILL, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Ninja\\ninja_climb.png", eSpriteID::SPRITE_NINJA_CLIMB, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Ninja\\ninja_sword.png", eSpriteID::SPRITE_SWORD_NINJA, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\EnemyRun\\enemy_run.png", eSpriteID::SPRITE_ENEMY_RUN, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\EnemySword\\enemy_sword.png", eSpriteID::SPRITE_ENEMY_SWORD, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\Boss\\alivejump.png", eSpriteID::SPRITE_BOSS, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\Boss\\bullet.png", eSpriteID::SPRITE_BULLET_BOSS, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\EnemyBrownBat\\alivemove.png", eSpriteID::SPRITE_ENEMY_BROWN_BAT, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\EnemyEagle\\alivemove.png", eSpriteID::SPRITE_ENEMY_EAGLE, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\EnemyMachineGun\\move.png", eSpriteID::SPRITE_ENEMY_MACHINE_GUN_MOVE, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\EnemyMachineGun\\shoot.png", eSpriteID::SPRITE_ENEMY_MACHINE_GUN_SHOOT, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\EnemyMachineGun\\bullet.png", eSpriteID::SPRITE_BULLET_ENEMY_MACHINE_GUN, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\EnemyPanther\\alivemove.png", eSpriteID::SPRITE_ENEMY_PANTHER, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\EnemyRocket\\idle.png", eSpriteID::SPRITE_ENEMY_ROCKET_IDLE, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\EnemyRocket\\shoot.png", eSpriteID::SPRITE_ENEMY_ROCKET_SHOOT, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\EnemyRocket\\bullet.png", eSpriteID::SPRITE_BULLET_ENEMY_ROCKET, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\EnemyThrowSword\\move.png", eSpriteID::SPRITE_ENEMY_THROW_SWORD_MOVE, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\EnemyThrowSword\\throw.png", eSpriteID::SPRITE_ENEMY_THROW_SWORD_SHOOT, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\EnemyThrowSword\\sword.png", eSpriteID::SPRITE_SWORD_ENEMY_THROW, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\explosion.png", eSpriteID::SPRITE_EXPLOSION, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\GifBird\\GifBird.png", eSpriteID::SPRITE_GIF_BIRD, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\GifButerfly\\GifButerfly.png", eSpriteID::SPRITE_GIF_BUTERFLY, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\ThrowStar.png", eSpriteID::SPRITE_THROW_STAR, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\Skill\\SkillThrowStar.png", eSpriteID::SPRITE_SKILL_THROW_STAR, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\Flames.png", eSpriteID::SPRITE_FLAMES, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\Skill\\SkillFlames.png", eSpriteID::SPRITE_SKILL_FLAMES, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\WindmilStar.png", eSpriteID::SPRITE_WINDMIL_STAR, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\Skill\\SkillWindmilStar.png", eSpriteID::SPRITE_SKILL_WINDMIL_STAR, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\5power.png", eSpriteID::SPRITE_5_POWER, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\10power.png", eSpriteID::SPRITE_10_POWER, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\1000point.png", eSpriteID::SPRITE_1000_POINT, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\500point.png", eSpriteID::SPRITE_500_POINT, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\health.png", eSpriteID::SPRITE_HEALTH, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\TimeFreeze.png", eSpriteID::SPRITE_FREEZE, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\healthbarfull.png", eSpriteID::SPRITE_HEALTH_BAR_FULL, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\healthbarlost.png", eSpriteID::SPRITE_HEALTH_BAR_EMPTY, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Item\\iconItem.png", eSpriteID::SPRITE_ICON_ITEM, 1, 1, 1);
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

