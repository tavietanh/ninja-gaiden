#ifndef VIRTUAL_OBJECT_H
#define VIRTUAL_OBJECT_H

#include "CObjectDx9.h"

class VirtualObject : public CObjectDx9
{
	int m_Width;
	int m_Height;
public:
	int getWidth() const { return m_Width; };
	int getHeight() const { return m_Height; };
	virtual RECT getBound();
	VirtualObject(void);
	VirtualObject(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(CObjectDx9* checkingObject);
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	VirtualObject(D3DXVECTOR3 _position, int _width, int _height, eObjectID _ObjectID);
	~VirtualObject(void);
};

#endif