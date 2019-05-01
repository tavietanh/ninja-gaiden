#include "DynamicObject.h"



DynamicObject::DynamicObject()
{
}
DynamicObject::DynamicObject(D3DXVECTOR3 _position, eDirection _direction):CObjectDx9(_position, _direction)
{

}
void DynamicObject::UpdateBound()
{
	CObjectDx9::getBound();
}

DynamicObject::~DynamicObject()
{
}
