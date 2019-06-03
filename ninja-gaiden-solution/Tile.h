#ifndef TILE_H
#define TILE_H

#include "CObjectDx9.h"
#include "CGlobal.h"

class Tile : public CObjectDx9
{
	char m_ID;
public:
	Tile(void);
	Tile(D3DXVECTOR3 _position, int _ID, eSpriteID tileMapID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(CObjectDx9* checkingObject);

	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~Tile(void);
};
#endif
