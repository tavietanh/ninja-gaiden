#pragma once
#include <d3dx9.h>
#include <limits>
#include <algorithm>

class Collision
{
private:

public:
	struct Box
	{
		// position of top-left corner
		float x, y;

		// dimensions
		float w, h;

		// velocity
		float vx, vy;
	};
	Box box(RECT rect,float velocity);
	bool AABBCheck(Box b1, Box b2);
	float SweptAABB(Box b1, Box b2, float& normalx, float& normaly);
	Collision(void);
	~Collision(void);
};

