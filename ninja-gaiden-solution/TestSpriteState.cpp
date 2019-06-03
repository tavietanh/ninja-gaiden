#include "TestSpriteState.h"
int Move = 0;
void TestSpriteState::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	m_Grid = new Grid();
	m_Ninja = new Ninja(D3DXVECTOR3(50,80 , 1), eDirection::RIGHT, eObjectID::NINJA);
	Camera::getInstance()->Reset();
	string mapPath = "resources\\Map\\" + to_string(map) + "\\" + to_string(map) + ".xml";
	m_Grid->BuildGrid(mapPath.c_str(), (eSpriteID)(map));
}

float scalexxx = 1.0f;

void TestSpriteState::HandleInput()
{
	m_Ninja->HandleInput();
}

void TestSpriteState::Update()
{

	Camera::getInstance()->UpdateCamera(&m_Ninja->getPositionVec3());
	
	m_Ninja->UpdateAnimation();
	m_Ninja->UpdateMovement();
	m_Ninja->SetFlag();
	m_Grid->InsertObjectIntoView(Camera::getInstance()->getBound(), m_Grid->m_cells);
	m_Grid->Update();
	m_Grid->UpdateAnimation();
	m_Grid->UpdateMovement();
	for (int i = 0; i < (int)m_Grid->mListObjectCollisionInView.size(); ++i)
	{
		m_Ninja->UpdateCollision(m_Grid->mMapObjectCollisionInGame[m_Grid->mListObjectCollisionInView[i]]);
		m_Grid->UpdateCollision(m_Grid->mMapObjectCollisionInGame[m_Grid->mListObjectCollisionInView[i]]);
	}
}
void TestSpriteState::Render(SPRITEHANDLE _lpDSpriteHandle)
{
	m_Grid->Render(_lpDSpriteHandle);
	m_Ninja->Render(_lpDSpriteHandle);
}

void TestSpriteState::Pause()
{

}

void TestSpriteState::Resume()
{

}

void TestSpriteState::Release()
{
	
}
