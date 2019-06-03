#include "EnemyEagle.h"


EnemyEagle::EnemyEagle()
{
}

EnemyEagle::EnemyEagle(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void EnemyEagle::Initialize()
{

}

void EnemyEagle::UpdateAnimation()
{

}

bool EnemyEagle::CanCollisionWithVirtualObject(VirtualObject* virtualObject)
{
	return 0;
}

void EnemyEagle::UpdateCollision(CObjectDx9* checkingObject)
{

}
void EnemyEagle::UpdateMovement()
{

}
void EnemyEagle::Update()
{

}

void EnemyEagle::Render(SPRITEHANDLE spriteHandle)
{
}

void EnemyEagle::Release()
{

}
EnemyEagle::~EnemyEagle()
{
}


