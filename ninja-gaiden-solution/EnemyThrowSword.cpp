#include "EnemyThrowSword.h"


EnemyThrowSword::EnemyThrowSword()
{
}

EnemyThrowSword::EnemyThrowSword(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void EnemyThrowSword::Initialize()
{

}

void EnemyThrowSword::UpdateAnimation()
{

}

bool EnemyThrowSword::CanCollisionWithVirtualObject(VirtualObject* virtualObject)
{
	return 0;
}

void EnemyThrowSword::UpdateCollision(CObjectDx9* checkingObject)
{

}
void EnemyThrowSword::UpdateMovement()
{

}
void EnemyThrowSword::Update()
{

}

void EnemyThrowSword::Render(SPRITEHANDLE spriteHandle)
{
}

void EnemyThrowSword::Release()
{

}
EnemyThrowSword::~EnemyThrowSword()
{
}


