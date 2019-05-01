#include "Tile.h"


Tile::Tile(void)
{
}

Tile::Tile(D3DXVECTOR3 _position, int ID, eSpriteID tileMapID)
{
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(tileMapID));
	m_Sprite->getAnimation()->setSourceRectAtIndex(ID);
	m_ID = ID;
	/*RECT temp = *m_Sprite->getAnimation()->getSourceRect();
	temp.right = temp.right - 1;
	m_Sprite->getAnimation()->setSourceRect(temp);*/
}

void Tile::Initialize()
{

}
void Tile::UpdateAnimation()
{

}

void Tile::Update()
{
}

void Tile::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, getPositionVec2(), ESpriteEffect::None, 0.0f, 1.0f, 0.4f);
}

void Tile::Release()
{
}

Tile::~Tile(void)
{
}