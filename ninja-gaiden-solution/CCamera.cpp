#include "CCamera.h"

Camera* Camera::s_Instance = 0;

Camera::Camera()
{
	D3DXMatrixIdentity(&m_matrixTranslate);
	m_matrixTranslate._41 = 0;
	m_matrixTranslate._42 = SCREEN_HEIGHT;
	m_matrixTranslate._22 = -1.0f;
	m_isLockWidth = false;
	m_isCheckFlagX = false;
	m_flagStartAutoRun = D3DXVECTOR2(0, 0);
	m_flagStopAutoRun = D3DXVECTOR2(0, 0);
	m_isPause = false;
}



void Camera::Reset()
{
	D3DXMatrixIdentity(&m_matrixTranslate);
	m_matrixTranslate._41 = 0;
	m_matrixTranslate._42 = SCREEN_HEIGHT;
	m_matrixTranslate._22 = -1.0f;
	m_isLockWidth = false;
	m_isCheckFlagX = false;
	m_isCheckFlagY = false;
	m_flagStartAutoRun = D3DXVECTOR2(0, 0);
	m_flagStopAutoRun = D3DXVECTOR2(0, 0);
	m_isPause = false;
}

Camera* Camera::getInstance()
{
	if (s_Instance == 0)
	{
		s_Instance = new Camera();
	}
	return s_Instance;
}

RECT Camera::getBound()
{
	RECT tempRect = RECT();

	tempRect.top = (long)(m_matrixTranslate._42);
	tempRect.left = (long)(-m_matrixTranslate._41);
	tempRect.right = (long)(tempRect.left + SCREEN_WIDTH);
	tempRect.bottom = (long)(tempRect.top - SCREEN_HEIGHT);

	return tempRect;
}

void Camera::UpdateCamera(D3DXVECTOR3* cameramanLocation)
{
	if (cameramanLocation->x < SCREEN_WIDTH/2|| (cameramanLocation->x+ SCREEN_WIDTH / 2)>m_MaxWidth)
	{
		m_isLockWidth = true;
	}
	else
	{
		m_matrixTranslate._41 = (float)((int)(-(cameramanLocation->x - SCREEN_WIDTH / 2)));
		m_isLockWidth = false;
	}
	this->m_previousPosition.x = m_matrixTranslate._41;
	if (m_isCheckFlagX)
	{
		if ((getBound().right - SCREEN_WIDTH / 2) > m_flagStartAutoRun.x)
		{
			m_matrixTranslate._41 -= 1;
			m_isPause = true;
		}
		if ((getBound().right - SCREEN_WIDTH / 2) >= m_flagStopAutoRun.x)
		{
			m_isCheckFlagX = false;
			m_isLockWidth = true;
			m_isPause = false;
		}
	}

}

D3DXMATRIX Camera::GetMatrixTranslate()
{
	return m_matrixTranslate;
}

Camera::~Camera()
{
	SAFE_DELETE(s_Instance);
}