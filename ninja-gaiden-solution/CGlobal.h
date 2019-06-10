#ifndef CGLOBAL_H
#define CGLOBAL_H

#include "EObjectID.h"
#include "CObjectDx9.h"
#include "EIDItem.h"

class CGlobal
{
public:
	static int	Ninja_X;
	static int	Ninja_Y;
	static bool IsExit;
	static bool IsMute;
	static bool IsWindowMode;
	static int	MapName;
	static int	MapWidth;
	static int	MapHeight;
	static int	healthNinja;
	static int	healthBoss;
	static eIDItem Item;
	static int score;
};

bool IsMovementObject(eObjectID type);
float Distance(CObjectDx9*, CObjectDx9*);
#endif
