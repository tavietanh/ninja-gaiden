#include "GifButerfly.h"


GifButerfly::GifButerfly()
{
}

GifButerfly::GifButerfly(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID, eObjectID idItem)
	: DynamicObject(_position, _direction, _objectID)
{
}

void GifButerfly::Initialize()
{

}

void GifButerfly::UpdateAnimation()
{

}

bool GifButerfly::CanCollisionWithVirtualObject(VirtualObject* virtualObject)
{
	return 0;
}

void GifButerfly::UpdateCollision(CObjectDx9* checkingObject)
{

}
void GifButerfly::UpdateMovement()
{

}
void GifButerfly::Update()
{

}

void GifButerfly::Render(SPRITEHANDLE spriteHandle)
{
}

void GifButerfly::Release()
{

}
GifButerfly::~GifButerfly()
{
}


