#ifndef NINJA_H
#define NINJA_H
#include "DynamicObject.h"
#include "CInputDx9.h"
#include "NinjaSpirte.h"
#include "EDirection.h"
#include "CGlobal.h"

using namespace std;
class Ninja : public DynamicObject
{
	NinjaSpirte* m_NinjaSprite;
	float prePosX;
	float finalPosX;
public:
	Ninja();
	Ninja(D3DXVECTOR3 _position, eDirection _direction);
	void Render(SPRITEHANDLE spriteHandle);
	void HandleInput();
	void Update();
	void UpdateAnimation();
	void UpdateMovement();
	~Ninja();
};
#endif
