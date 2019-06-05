#include "ItemManager.h"

ItemManager*	ItemManager::_instance = 0;

ItemManager*	ItemManager::getInstance()
{
	if (!_instance)
	{
		_instance = new ItemManager();
	}
	return _instance;
}

void ItemManager::AddElement(DynamicObject* object)
{
	object->Initialize();
	object->getPhysic()->setAccelerate(D3DXVECTOR2(0.0f, ACCEL_ITEM_Y));
	object->getPhysic()->setVelocity(D3DXVECTOR2(0.0f, 1.1f));
	m_ListItem.push_back(object);
}

void ItemManager::Update()
{
	if (m_ListItem.empty() != true)
	{
		for (list<DynamicObject*>::iterator i = m_ListItem.begin(); i != m_ListItem.end(); )
		{

			(*i)->UpdateAnimation();
			(*i)->UpdateMovement();
			(*i)->Update();
				i++;
		}
	}
}

void ItemManager::UpdateCollision(CObjectDx9* checkingObject)
{
	if (m_ListItem.empty() != true)
	{
		for (list<DynamicObject*>::iterator i = m_ListItem.begin(); i != m_ListItem.end();)
		{
			(*i)->UpdateCollision(checkingObject);

			if ((*i)->getObjectState() == STATE_DEATH)
			{
				SAFE_DELETE(*i);
				i = m_ListItem.erase(i);
			}
			else
			{
				i++;
			}
		}
	}
}

void ItemManager::Render(SPRITEHANDLE spriteHandle)
{
	if (m_ListItem.empty() != true)
	{
		for (list<DynamicObject*>::iterator i = m_ListItem.begin(); i != m_ListItem.end(); i++)
		{
			(*i)->Render(spriteHandle);
		}
	}
}

void ItemManager::Release()
{
	for (list<DynamicObject*>::iterator i = m_ListItem.begin(); i != m_ListItem.end(); i++)
	{
		(*i)->Release();
		SAFE_DELETE(*i);
	}
	m_ListItem.clear();
}
