#include "Cell.h"



Cell::Cell()
{
}
Cell::Cell(int _ID, RECT _bound)
{
	this->mID = _ID;
	this->mBound = _bound;
}

Cell::~Cell()
{
}
