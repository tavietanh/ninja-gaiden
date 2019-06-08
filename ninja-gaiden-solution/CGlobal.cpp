
#include "CGlobal.h"


int CGlobal::Ninja_X = 0;
int CGlobal::Ninja_Y = 0;
bool CGlobal::IsWindowMode = true;
bool CGlobal::IsExit = false;
bool CGlobal::IsMute = false;

int CGlobal::MapName = 0;
int	CGlobal::MapWidth = 0;
int	CGlobal::MapHeight = 0;
bool IsMovementObject(eObjectID id)
{
	switch (id)
	{
		case eObjectID::ENEMY_SWORD:
		case eObjectID::ENEMY_THROW_SWORD:
		case eObjectID::ENEMY_BROWN_BAT:
		case eObjectID::ENEMY_EAGLE:
		case eObjectID::ENEMY_PANTHER:
		case eObjectID::ENEMY_MACHINE_GUN:
		case eObjectID::ENEMY_RUN:
		case eObjectID::BOSS_3:
		case eObjectID::OBJECT_5_POWER:
		case eObjectID::OBJECT_10_POWER:
		case eObjectID::OBJECT_500_POINT:
		case eObjectID::OBJECT_1000_POINT:
		case eObjectID::OBJECT_FLAMES:
		case eObjectID::OBJECT_THROW_STAR:
		case eObjectID::OBJECT_TIME_FREEZE:
		case eObjectID::OBJECT_WINDMIL_STAR:
		case eObjectID::OBJECT_HEALTH:
		return true;
	default:
		return false;
	}
	return false;
}
float Distance(CObjectDx9* a, CObjectDx9* b)
{
	float dx = abs(a->getPositionVec2().x - b->getPositionVec2().x);
	float dy = abs(a->getPositionVec2().y - b->getPositionVec2().y);

	return sqrtf(dx * dx + dy * dy);
}