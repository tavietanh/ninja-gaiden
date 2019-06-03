#include "Grid.h"



Grid::Grid()
{

	this->cell = NULL;
	this->mIsFirstLoadXml = true;
}
void Grid::InsertObjectIntoView(RECT viewPort, std::vector<Cell*> cells)
{
	
	if (this->mListObjectInView.size() > 0 && this->mListObjectCollisionInView.size() > 0)
	{
		this->mListObjectInView.clear();
		this->mListObjectCollisionInView.clear();
	}
	for (int a = 0; a < cells.size(); a++)
	{
		int j = 0;

		if (CheckAABB(ConvertToBox(viewPort), ConvertToBox(cells[a]->getBound())))
		{
			for (int i = 0; i < (int)cells[a]->mListObject.size(); ++i)
			{
				mListObjectInView.push_back(cells[a]->mListObject[i]);
			}

			for (int i = 0; i < (int)cells[a]->mListObjectCollision.size(); ++i)
			{
				if (mMapObjectCollisionInGame[cells[a]->mListObjectCollision[i]]->getObjectState() != eObjectState::STATE_DEATH && mMapObjectCollisionInGame[cells[a]->mListObjectCollision[i]]->getObjectState() != eObjectState::STATE_BOSS_DEATH)
				{

					for (j = 0; j < (int)mListObjectCollisionInView.size(); ++j)
					{
						if (cells[a]->mListObjectCollision[i] == mListObjectCollisionInView[j])
							break;
					}

					if (j == mListObjectCollisionInView.size())
					{

						mListObjectCollisionInView.push_back(cells[a]->mListObjectCollision[i]);
					}
				}
				else
				{
					cells[a]->mListObjectCollision.erase(cells[a]->mListObjectCollision.begin() + i);
				}
				//if (!CheckAABB(ConvertToBox(viewPort), ConvertToBox(mMapObjectCollisionInGame[cells[a]->mListObjectCollision[i]]->getBound())))
				//{
				//	mMapObjectCollisionInGame[cells[a]->mListObjectCollision[i]]->reset();
				//}
			}
		}
	}
}
void Grid::Release(Cell* cell)
{
	delete cell;
	cell = NULL;

	if (this->mMapObjectInGame.size() > 0)
		this->mMapObjectInGame.clear();

	if (this->mMapObjectCollisionInGame.size() > 0)
		this->mMapObjectCollisionInGame.clear();
}
void Grid::BuildGrid(const char* content, eSpriteID _tile_map)
{
	Cell* cell;
	if (this->mIsFirstLoadXml == true)
	{
		CMarkup xml;
		xml.Load(content);

		if (xml.FindElem("Map"))
		{
			CGlobal::MapName = atoi(xml.GetAttrib("Name").c_str());
			CGlobal::MapWidth = atoi(xml.GetAttrib("Width").c_str());
			CGlobal::MapHeight = atoi(xml.GetAttrib("Height").c_str());
		}
		xml.IntoElem();
		this->mIsFirstLoadXml = false;
		while (xml.FindElem("Cell"))
		{
			RECT bound = RECT();
			bound.left = atoi(xml.GetAttrib("X").c_str());
			bound.top = atoi(xml.GetAttrib("Y").c_str());
			bound.bottom = bound.top - atoi(xml.GetAttrib("Height").c_str());
			bound.right = bound.left + atoi(xml.GetAttrib("Width").c_str());
			cell = new Cell(atoi(xml.GetAttrib("Id").c_str()), bound);
			m_cells.push_back(cell);
			xml.IntoElem();
			if (xml.FindElem("Objects"))
			{
				xml.IntoElem();
				std::map<int, CObjectDx9*>::iterator i;
				while (xml.FindElem("Object"))
				{
					i = mMapObjectInGame.find(atoi(xml.GetAttrib("Index").c_str()));
					if (i == mMapObjectInGame.end())
					{
						if (atoi(xml.GetAttrib("Type").c_str()) == 0)
						{
							mMapObjectInGame[atoi(xml.GetAttrib("Index").c_str())] = new Tile(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f), atoi(xml.GetAttrib("Id").c_str()),
								_tile_map);
						}
						else if (atoi(xml.GetAttrib("Type").c_str()) == 1)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new VirtualObject(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								atoi(xml.GetAttrib("Width").c_str()),
								atoi(xml.GetAttrib("Height").c_str()),
								(eObjectID)atoi(xml.GetAttrib("Id").c_str()));
						}
						else if (atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::ENEMY_ROCKET)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new EnemyRocket(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								eDirection::LEFT,
								(eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if (atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::ENEMY_SWORD)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new EnemySword(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								0.0f),
								eDirection::LEFT,
								(eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if (atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::ENEMY_RUN)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new  EnemyRun(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								eDirection::LEFT,
								(eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if (atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::ENEMY_THROW_SWORD)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new  EnemyThrowSword(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								eDirection::LEFT,
								(eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if (atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::ENEMY_BROWN_BAT)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new EnemyBrownBat(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								eDirection::LEFT,
								(eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if (atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::ENEMY_EAGLE)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new EnemyEagle(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								eDirection::LEFT,
								(eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if (atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::GIF_BUTERFLY)
						{
							int tempIndex = atoi(xml.GetAttrib("Index").c_str());
							float tempPositionX = (float)(atoi(xml.GetAttrib("X").c_str()));
							float tempPositionY = (float)(atoi(xml.GetAttrib("Y").c_str()));
							int tempId = atoi(xml.GetAttrib("Id").c_str());
							xml.FindElem("Object");
							int temp = atoi(xml.GetAttrib("Id").c_str());
							mMapObjectCollisionInGame[tempIndex] = new GifButerfly(D3DXVECTOR3(
								tempPositionX,
								tempPositionY,
								1.0f),
								eDirection::LEFT,
								(eObjectID)tempId,
								(eObjectID)temp);
							mMapObjectCollisionInGame[tempIndex]->Initialize();
						}
						else if (atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::GIF_BIRD)
						{
							int tempIndex = atoi(xml.GetAttrib("Index").c_str());
							float tempPositionX = (float)(atoi(xml.GetAttrib("X").c_str()));
							float tempPositionY = (float)(atoi(xml.GetAttrib("Y").c_str()));
							int tempId = atoi(xml.GetAttrib("Id").c_str());
							xml.FindElem("Object");
							int temp = atoi(xml.GetAttrib("Id").c_str());
							mMapObjectCollisionInGame[tempIndex] = new GifBird(D3DXVECTOR3(
								tempPositionX,
								tempPositionY,
								1.0f),
								eDirection::LEFT,
								(eObjectID)tempId,
								(eObjectID)temp);
							mMapObjectCollisionInGame[tempIndex]->Initialize();
						}
						else if (atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::ENEMY_PANTHER)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new EnemyPanther(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								eDirection::LEFT,
								(eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if (atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::ENEMY_MACHINE_GUN)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new EnemyMachineGun(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								eDirection::LEFT,
								(eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if (atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::BOSS_3)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new Boss3(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								eDirection::LEFT,
								(eObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}

					}

					if (atoi(xml.GetAttrib("Type").c_str()) == (int)ETypeObject::TILE_MAP)
					{
						cell->mListObject.push_back(atoi(xml.GetAttrib("Index").c_str()));
					}
					else if (atoi(xml.GetAttrib("Type").c_str()) == (int)ETypeObject::VIRTUAL_OBJECT || atoi(xml.GetAttrib("Type").c_str()) == (int)ETypeObject::DYNAMIC_OBJECT)
					{
						if (atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::OBJECT_1000_POINT
							|| atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::OBJECT_10_POWER
							|| atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::OBJECT_500_POINT
							|| atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::OBJECT_5_POWER
							|| atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::OBJECT_FLAMES
							|| atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::OBJECT_HEALTH
							|| atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::OBJECT_THROW_STAR
							|| atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::OBJECT_TIME_FREEZE
							|| atoi(xml.GetAttrib("Id").c_str()) == (int)eObjectID::OBJECT_WINDMIL_STAR
							)
							cell->mListObjectCollision.push_back(atoi(xml.GetAttrib("Index").c_str()) - 1);
						else
							cell->mListObjectCollision.push_back(atoi(xml.GetAttrib("Index").c_str()));

					}
				}
			}
			xml.OutOfElem();
			xml.OutOfElem();
		}
	}
}
void Grid::Update()
{
	for (int i = 0; i < (int)mListObjectCollisionInView.size(); ++i)
	{
		mMapObjectCollisionInGame[mListObjectCollisionInView[i]]->Update();
	}
}
void Grid::UpdateAnimation()
{
	for (int i = 0; i < (int)mListObjectCollisionInView.size(); ++i)
	{
		mMapObjectCollisionInGame[mListObjectCollisionInView[i]]->UpdateAnimation();
	}
}

void Grid::UpdateCollision(CObjectDx9* checkingObject)
{
	for (int i = 0; i < (int)mListObjectCollisionInView.size(); ++i)
	{
		mMapObjectCollisionInGame[mListObjectCollisionInView[i]]->UpdateCollision(checkingObject);
	}
}

void Grid::UpdateMovement()
{
	for (int i = 0; i < (int)mListObjectCollisionInView.size(); ++i)
	{
		if (IsMovementObject(mMapObjectCollisionInGame[mListObjectCollisionInView[i]]->getID()))
		{
			DynamicObject* tempObject = (DynamicObject*)mMapObjectCollisionInGame[mListObjectCollisionInView[i]];
			tempObject->UpdateMovement();
		}
	}
}
void Grid::Render(SPRITEHANDLE spriteHandler)
{
	for (int i = 0; i < (int)mListObjectInView.size(); ++i)
	{
		mMapObjectInGame[mListObjectInView[i]]->Render(spriteHandler);
	}

	for (int j = 0; j < (int)mListObjectCollisionInView.size(); ++j)
	{
		mMapObjectCollisionInGame[mListObjectCollisionInView[j]]->Render(spriteHandler);
	}
}
Grid::~Grid()
{
}
