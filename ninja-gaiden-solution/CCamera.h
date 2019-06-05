#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <d3dx9.h>
#include <d3d9.h>
#include "FrameworkDefine.h"
#include <fstream>

using namespace std;
//#include "CGlobal.h"

class Camera
{
	static Camera*		s_Instance;
	D3DXVECTOR2	m_previousPosition;
	bool m_isLockWidth;
	bool m_isCheckFlagX;
	bool m_isCheckFlagY;
	int m_MaxWidth;
	D3DXVECTOR2 m_flagStartAutoRun;
	D3DXVECTOR2 m_flagStopAutoRun;
	bool m_isPause;
	Camera();
	D3DXMATRIX			m_matrixTranslate;
public:
	RECT getBound();
	void Reset();
	bool IsGamePause() { return m_isPause; }
	void setLockWidth(bool _isLock) { m_isLockWidth = _isLock; }
	void setMaxWidth(int maxWidth) { m_MaxWidth = maxWidth; }
	static Camera*		getInstance();
	void				UpdateCamera(D3DXVECTOR3* cameramanLocation);
	D3DXMATRIX			GetMatrixTranslate();
	~Camera();
};

#endif
