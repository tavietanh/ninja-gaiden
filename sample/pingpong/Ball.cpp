#include "Ball.h"


Ball::Ball(void)
{
}

void Ball::Init(MContent* content)
{
	this->img = content->LoadTexture("./ball.png");
	this->position = D3DXVECTOR2(0,0);
	dx = dy = 1;
}
void Ball::Update(float gameTime)
{
	float speed = 5;
	if(position.x < 0 || position.x + 40.0 > 300)
		dx = -dx;
	if(position.y < 0 || position.y + 40.0 > 600)
		dy = -dy;
	position.x += dx * speed;
	position.y += dy * speed;
	rect.left = position.x;
	rect.top = position.y;
	rect.right =  40;
	rect.bottom =  40;
}
void Ball::Render(MGraphic* graphic)
{
	graphic->DrawTexture(this->img,this->position,D3DCOLOR_XRGB(255,255,255));
}


Ball::~Ball(void)
{
}
