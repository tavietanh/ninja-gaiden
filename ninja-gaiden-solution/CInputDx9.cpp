#include "CInputDx9.h"

CInputDx9::CInputDx9() :
	m_lpDirectInput(0),
	m_lpKeyBoardDevice(0),
	m_lpMouseDevice(0)
{
	m_cursorLocation.x = 0;
	m_cursorLocation.y = 0;
}

CInputDx9* CInputDx9::s_Instance = 0;

CInputDx9* CInputDx9::getInstance()
{
	if (s_Instance == 0)
	{
		s_Instance = new CInputDx9();
	}
	return s_Instance;
}

void CInputDx9::InitializeInput()
{
	HRESULT result;

	result = DirectInput8Create(
		GetModuleHandle(0),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_lpDirectInput,
		0);




	result = m_lpDirectInput->CreateDevice(GUID_SysKeyboard, &m_lpKeyBoardDevice, 0);



	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = 1024; // Arbitary buffer size

	HRESULT hr = m_lpKeyBoardDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK) return;


	result = m_lpDirectInput->CreateDevice(GUID_SysMouse, &m_lpMouseDevice, 0);


	for (int i = 0; i < 256; i++)
	{
		m_PressKey[i] = false;
		m_currentBuffer[i] = 0;
		m_previousBuffer[i] = 0;
	}
}

void CInputDx9::InitializeKeyBoardDevice(HWND handleWindow)
{
	HRESULT result;
	result = m_lpKeyBoardDevice->SetDataFormat(&c_dfDIKeyboard);


	result = m_lpKeyBoardDevice->SetCooperativeLevel(handleWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);


	result = m_lpKeyBoardDevice->Acquire();

}

void CInputDx9::InitializeMouseDevice(HWND handleWindow)
{
	HRESULT result;

	ZeroMemory(&m_mouseState, sizeof(m_mouseState));

	result = m_lpMouseDevice->SetDataFormat(&c_dfDIMouse2);

	

	result = m_lpMouseDevice->SetCooperativeLevel(handleWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	
	result = m_lpMouseDevice->Acquire();
	
}


void CInputDx9::UpdateKeyBoard()
{
	memcpy(m_previousBuffer, m_currentBuffer, 256);
	m_lpKeyBoardDevice->Acquire(); // Acquire device
	m_lpKeyBoardDevice->GetDeviceState(sizeof(m_currentBuffer), (LPVOID)&m_currentBuffer);

	DWORD dwElements = 1024;
	HRESULT hr = m_lpKeyBoardDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_KeyEvents, &dwElements, 0);

	if (!FAILED(hr))
	{
		for (DWORD i = 0; i < dwElements; i++)
		{
			int KeyCode = m_KeyEvents[i].dwOfs;
			int KeyState = m_KeyEvents[i].dwData;
			if ((KeyState & 0x80) > 0)
				m_PressKey[KeyCode] = true;
			else
				m_PressKey[KeyCode] = false;
		}
	}
	else
	{
		for (int i = 0; i < 256; i++)
		{
			m_PressKey[i] = false;
		}
	}
}

bool CInputDx9::IsKeyDown(int keyCode)
{
	if (m_currentBuffer[keyCode] & 0x00000080)
	{
		return true;
	}
	return false;
}

bool CInputDx9::IsKeyUp(int keyCode)
{
	if (m_currentBuffer[keyCode] & 0x00000080)
	{
		return false;
	}
	return true;
}

void CInputDx9::SetKeyDown(int keyCode)
{
	m_currentBuffer[keyCode] |= 0x00000080;
}

void CInputDx9::SetKeyUp(int keyCode)
{
	m_currentBuffer[keyCode] &= 0x00000000;
}


bool CInputDx9::IsKeyPress(int keyCode)
{
	if (
		(m_currentBuffer[keyCode] & 0x00000080) &&
		!(m_previousBuffer[keyCode] & 0x00000080))
	{
		return true;
	}
	return false;
	//	return m_PressKey[keyCode];
}

bool CInputDx9::IsKeyRelease(int keyCode)
{
	if (
		!(m_currentBuffer[keyCode] & 0x00000080) &&
		(m_previousBuffer[keyCode] & 0x00000080))
	{
		return true;
	}
	return false;
	/*return !m_PressKey[keyCode];*/
}

void CInputDx9::UpdateMouse()
{
	memcpy(m_previousMouseState.rgbButtons, m_mouseState.rgbButtons, 8);
	ZeroMemory(&m_mouseState, sizeof(m_mouseState));
	HRESULT result = m_lpMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), (LPVOID)&m_mouseState);

	m_cursorLocation.x += m_mouseState.lX;
	m_cursorLocation.y += m_mouseState.lY;

	if (FAILED(result))
	{
		ZeroMemory(&m_mouseState, sizeof(m_mouseState));
		m_lpMouseDevice->Acquire();
	}

}

D3DXVECTOR2 CInputDx9::GetCursorLocation()
{
	return D3DXVECTOR2((float)m_mouseState.lX, (float)m_mouseState.lY);
}

void CInputDx9::Release()
{
	SAFE_RELEASE(m_lpDirectInput);
	SAFE_RELEASE(m_lpKeyBoardDevice);
	SAFE_RELEASE(m_lpMouseDevice);
}

CInputDx9::~CInputDx9()
{
	Release();
}