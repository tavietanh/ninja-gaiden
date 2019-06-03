#include "GifBird.h"


GifBird::GifBird()
{
}

GifBird::GifBird(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID, eObjectID idItem)
	: DynamicObject(_position, _direction, _objectID)
{
}

void GifBird::Initialize()
{

}

void GifBird::UpdateAnimation()
{

}

bool GifBird::CanCollisionWithVirtualObject(VirtualObject* virtualObject)
{
	return 0;
}

void GifBird::UpdateCollision(CObjectDx9* checkingObject)
{

}
void GifBird::UpdateMovement()
{

}
void GifBird::Update()
{

}

void GifBird::Render(SPRITEHANDLE spriteHandle)
{
}

void GifBird::Release()
{

}
GifBird::~GifBird()
{
}


