#ifndef __ITEM_MANAGER_H__
#define __ITEM_MANAGER_H__
#include "DynamicObject.h"
#include <list>
using namespace std;


class ItemManager
{
private:
	ItemManager() {}
	~ItemManager() {}
	static ItemManager*		_instance;
	list<DynamicObject*>		m_ListItem;

public:
	static ItemManager*	getInstance();
	void AddElement(DynamicObject* objectWeaponry);
	void UpdateCollision(CObjectDx9* checkingObject);
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
};

#endif
