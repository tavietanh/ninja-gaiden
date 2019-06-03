#include "Boss3.h"


Boss3::Boss3()
{
}

Boss3::Boss3(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void Boss3::Initialize()
{

}

void Boss3::UpdateAnimation()
{

}

bool Boss3::CanCollisionWithVirtualObject(VirtualObject* virtualObject)
{
	return 0;
}

void Boss3::UpdateCollision(CObjectDx9* checkingObject)
{

}
void Boss3::UpdateMovement()
{

}
void Boss3::Update()
{

}

void Boss3::Render(SPRITEHANDLE spriteHandle)
{
}

void Boss3::Release()
{

}
Boss3::~Boss3()
{
}


