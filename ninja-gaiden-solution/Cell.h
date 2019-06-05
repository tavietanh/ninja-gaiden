#ifndef CELL_H
#define CELL_H

#include "CObjectDx9.h"
#include <list>
#include <vector>
#include "Collision.h"
#include "Tile.h"
#include "VirtualObject.h"

class Cell
{
private:
	int mID;
	RECT mBound;
	bool inView;
public:
	std::vector<int> mListObject;
	std::vector<int> mListObjectCollision;

	int getID() const { return this->mID; };
	RECT getBound() const { return this->mBound; };
	std::vector<int> getListObject() const { return this->mListObject; };
	std::vector<int> getListObjectCollision() const { return this->mListObjectCollision; };
	bool isInView = false;
	Cell();
	Cell(int, RECT);
	~Cell();
};

#endif