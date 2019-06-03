#include "EnemyPanther.h"


EnemyPanther::EnemyPanther()
{
}

EnemyPanther::EnemyPanther(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void EnemyPanther::Initialize()
{

}

void EnemyPanther::UpdateAnimation()
{

}

bool EnemyPanther::CanCollisionWithVirtualObject(VirtualObject* virtualObject)
{
	return 0;
}

void EnemyPanther::UpdateCollision(CObjectDx9* checkingObject)
{

}
void EnemyPanther::UpdateMovement()
{

}
void EnemyPanther::Update()
{

}

void EnemyPanther::Render(SPRITEHANDLE spriteHandle)
{
}

void EnemyPanther::Release()
{

}
EnemyPanther::~EnemyPanther()
{
}


