#include<Windows.h>
#include"DirectGraphics.h"
#include"DirectInput.h"

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

LRESULT CALLBACK WindowProcedure(HWND window_handle, UINT message_id, WPARAM wparam, LPARAM lparam)
{
	switch (message_id)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(window_handle, message_id, wparam, lparam);
		break;
	}
	return 0;
}


int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmpLine,
	INT nCmdShow)
{
	WNDCLASS window_class =
	{
		//○は覚えた方が良い
		CS_HREDRAW | CS_VREDRAW,			
		WindowProcedure,					
		0,									
		0,									
		hInstance,							
		LoadIcon(NULL, IDI_APPLICATION),	
		LoadCursor(NULL, IDC_ARROW),		
		nullptr,							
		nullptr,							
		TEXT("WindowClass"),				
	};

	if (RegisterClass(&window_class) == 0)
	{
		return 0;
	}

	int width = 640;
	int height = 480;
	float rotate = 0.0f;
	float go = 0.0f;
	float slide = 0.0f;

	// ウィンドウ作成
	HWND window_handle = CreateWindow(
		TEXT("WindowClass"),
		TEXT("ウィンドウ生成サンプル"),
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME),
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		NULL);

	RECT window_rect;
	if (GetWindowRect(window_handle, &window_rect) == false)
	{
		return 0;
	}

	RECT client_rect;
	if (GetClientRect(window_handle, &client_rect) == false)
	{
		return 0;
	}
	int frame_size_x = (window_rect.right - window_rect.left) - (client_rect.right - client_rect.left);
	int frame_size_y = (window_rect.bottom - window_rect.top) - (client_rect.bottom - client_rect.top);
	int resize_width = frame_size_x + width;
	int resize_height = frame_size_y + height;

	SetWindowPos(
		window_handle,
		nullptr,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		resize_width,
		resize_height,
		SWP_NOMOVE
	);
	ShowWindow(window_handle, SW_SHOW);


	if (InitDirectGraphics(window_handle) == false)
	{
		return 0;
	}
	if (InitDirectInput() == false)
	{
		return 0;
	}
	if (LoadTexture(TextureID::Tex1) == false)
	{
		return 0;
	}

	LoadXFile(TEXT("WitchWait.x"));
	while (true)
	{
		MSG message;


		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
			{
				break;
			}
			else {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		else
		{
			UpdateDirectInput();


			SetUpProjection();

			StartDrawing();

			Draw3DPorigon();

			if (IsKeyHeld(DIK_RIGHT))
			{
				rotate += 0.5f;
			}
			else if (IsKeyHeld(DIK_LEFT))
			{
				rotate -= 0.5f;
			}
			if (IsKeyHeld(DIK_UP))
			{
				go -= 0.5f;
			}
			else if (IsKeyHeld(DIK_DOWN))
			{
				go += 0.5f;
			}
			if (IsKeyHeld(DIK_D))
			{
				slide -= 0.5f;
			}
			else if (IsKeyHeld(DIK_A))
			{
				slide += 0.5f;
			}

			DrawXFile(rotate, go, slide);

			UpdateCamera(rotate, go, slide);

			UpdateDirectInput();



			FinishDrawing();
		}


	}
	ReleaseTexture();

	ReleaseDirectGraphics();
	ReleaseDirectInput();


	return 0;
}