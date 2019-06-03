#ifndef GRID_H
#define GRID_H

#include "Cell.h"
#include "Collision.h"
#include "Markup.h"
#include <list>
#include <vector>
#include <map>
#include <unordered_set>
#include "EnemyRun.h"
#include "EnemySword.h"
#include "EnemyBrownBat.h"
#include "EnemyEagle.h"
#include "EnemyMachineGun.h"
#include "EnemyPanther.h"
#include "EnemyRocket.h"
#include "EnemyThrowSword.h"
#include "GifBird.h"
#include "GifButerfly.h"
#include "Boss3.h"

class Grid
{
private:
	RECT mBoundWorld;
	bool mIsFirstLoadXml;
	int mCount[100];
public:
	std::vector<int> mListObjectInView;
	std::vector<int> mListObjectCollisionInView;
	std::map<int, CObjectDx9*> mMapObjectInGame;
	std::map<int, CObjectDx9*> mMapObjectCollisionInGame;
	std::vector<Cell*> m_cells;
	Cell* cell;
	Cell* getRootCell() const { return this->cell; };
	RECT getBoundWorld() const { return this->mBoundWorld; };
	Grid();
	void InsertObjectIntoView(RECT, std::vector<Cell*>);
	void BuildGrid(const char* content, eSpriteID _tile_map);
	void Update();
	void UpdateAnimation();
	void UpdateCollision(CObjectDx9*);
	void UpdateMovement();
	void Release(Cell*);
	void Render(SPRITEHANDLE);
	~Grid();
};
#endif