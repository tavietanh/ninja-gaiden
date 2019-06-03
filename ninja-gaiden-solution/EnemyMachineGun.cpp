#include "EnemyMachineGun.h"


EnemyMachineGun::EnemyMachineGun()
{
}

EnemyMachineGun::EnemyMachineGun(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void EnemyMachineGun::Initialize()
{

}

void EnemyMachineGun::UpdateAnimation()
{

}

bool EnemyMachineGun::CanCollisionWithVirtualObject(VirtualObject* virtualObject)
{
	return 0;
}

void EnemyMachineGun::UpdateCollision(CObjectDx9* checkingObject)
{

}
void EnemyMachineGun::UpdateMovement()
{

}
void EnemyMachineGun::Update()
{

}

void EnemyMachineGun::Render(SPRITEHANDLE spriteHandle)
{
}

void EnemyMachineGun::Release()
{

}
EnemyMachineGun::~EnemyMachineGun()
{
}


