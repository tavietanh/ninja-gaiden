#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include "CSpriteDx9.h"
#include "eSpriteID.h"
#include <map>

using namespace std;

class SpriteManager
{
private:
	map<eSpriteID, CSpriteDx9*> m_ListSprite;
	SpriteManager(void);
	static 			SpriteManager* s_Instance;
	void 			LoadSpriteContent(LPDIRECT3DDEVICE9 _lpDirectDevice, const char* fileName, eSpriteID SpriteID, int Column, int Row, int TotalFrame);
public:
	CSpriteDx9*		getSprite(eSpriteID eID);
	void 			InitializeListSprite(LPDIRECT3DDEVICE9 _lpDirectDevice);
	void 			Release();
	static 			SpriteManager* getInstance();
	~SpriteManager(void);
};
#endif