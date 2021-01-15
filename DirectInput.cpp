#include "DirectInput.h"
LPDIRECTINPUT8 g_InputInterface;
LPDIRECTINPUTDEVICE8 g_InputKeyBoardDevice;
InputState g_KeyStates[256];

InputState UpdateInputState(bool is_push, InputState state);

InputState UpdateInputState(bool is_push, InputState state)
{
	if (is_push == true)
	{
		if (state == InputState::None)
		{
			return InputState::Pushed;
		}
		else if (state == InputState::Pushed || state == InputState::Held)
		{
			return InputState::Held;
		}
	}
	else
	{
		if (state == InputState::Pushed || state == InputState::Held)
		{
			return InputState::Released;
		}
	}
	return InputState::None;
}


bool InitDirectInput()
{
	HRESULT hr = DirectInput8Create(
		GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION,			
		IID_IDirectInput8,				
		(void**)&g_InputInterface,
		nullptr
	);

	if (FAILED(hr))
	{
		return false;
	}

	
	hr = g_InputInterface->CreateDevice(
		GUID_SysKeyboard,
		&g_InputKeyBoardDevice,
		NULL);
	if (FAILED(hr))
	{
		return false;
	}

	hr = g_InputKeyBoardDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		return false;
	}



	hr = g_InputKeyBoardDevice->SetCooperativeLevel(
		FindWindow(TEXT("WindowClass"), nullptr),
		DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr))
	{
		return false;
	}
	hr = g_InputKeyBoardDevice->Acquire();

	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

void ReleaseDirectInput()
{
	if (g_InputKeyBoardDevice != nullptr)
	{
		g_InputKeyBoardDevice->Unacquire();

		g_InputKeyBoardDevice->Release();
		g_InputKeyBoardDevice = nullptr;
	}
	if (g_InputInterface != nullptr)
	{
		g_InputInterface->Release();
		g_InputInterface = nullptr;
	}
}

void UpdateDirectInput()
{
	BYTE key_states[256];
	HRESULT hr;

	hr = g_InputKeyBoardDevice->GetDeviceState(
		256,
		key_states);
	if (SUCCEEDED(hr))
	{
		for (int i = 0; i < 256; i++)
		{
			bool is_push = false;
			if (key_states[i] & 0x80)
			{
				is_push = true;

			}
			g_KeyStates[i] = UpdateInputState(is_push, g_KeyStates[i]);
		}
		if (key_states[DIK_A] & 0x80)
		{

		}
	}
}

bool IsKeyHeld(int key)
{
	if (key < 0 || key >= 256)
	{
		return false;
	}
	return g_KeyStates[key] == InputState::Held ? true : false;
}

bool IsKeyPushed(int key)
{
	if (key < 0 || key >= 256)
	{
		return false;
	}

	if (g_KeyStates[key] == InputState::Pushed)
	{
		return true;
	}
	return false;
}

bool IsKeyPeleased(int key)
{
	if (key < 0 || key >= 256)
	{
		return false;
	}
	return g_KeyStates[key] == InputState::Released ? true : false;
}