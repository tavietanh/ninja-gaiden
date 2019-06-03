#include "EnemyRocket.h"


EnemyRocket::EnemyRocket()
{
}

EnemyRocket::EnemyRocket(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void EnemyRocket::Initialize()
{

}

void EnemyRocket::UpdateAnimation()
{

}

bool EnemyRocket::CanCollisionWithVirtualObject(VirtualObject* virtualObject)
{
	return 0;
}

void EnemyRocket::UpdateCollision(CObjectDx9* checkingObject)
{

}
void EnemyRocket::UpdateMovement()
{

}
void EnemyRocket::Update()
{

}

void EnemyRocket::Render(SPRITEHANDLE spriteHandle)
{
}

void EnemyRocket::Release()
{

}
EnemyRocket::~EnemyRocket()
{
}


