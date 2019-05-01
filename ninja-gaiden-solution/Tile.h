#ifndef TILE_H
#define TILE_H

#include <d3dx9.h>
#include "FrameworkDefine.h"
#include "ESpriteID.h"
#include "CSpriteDx9.h"
#include "SpriteManager.h"

class Tile
{

	char m_ID;
protected: 
	CSpriteDx9*		m_Sprite;
	D3DXVECTOR3		m_Position;
public:
	Tile(void);
	Tile(D3DXVECTOR3 _position, int _ID, eSpriteID tileMapID);
	void			setPosition(D3DXVECTOR3 _position) { m_Position = _position; }
	void			setPositionX(float _X) { m_Position.x = _X; }
	void			setPositionY(float _Y) { m_Position.y = _Y; }
	void			setPositionZ(float _Z) { m_Position.z = _Z; }
	D3DXVECTOR3		getPositionVec3() { return m_Position; }
	void Initialize();
	void UpdateAnimation();
	D3DXVECTOR2		getPositionVec2() { return D3DXVECTOR2(m_Position.x, m_Position.y); }
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~Tile(void);
};

#endif
