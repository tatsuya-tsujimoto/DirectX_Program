#include<Windows.h>

LRESULT CALLBACK WindowProcedure(HWND window_handle, UINT message_id, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(window_handle, message_id, wparam, lparam);
}

int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmoLine,
	INT nCmdShow)
{
	WNDCLASSA window_class =
	{
		CS_HREDRAW | CS_VREDRAW,
		WindowProcedure,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		nullptr,
		nullptr,
		"WindowClass",
	};
	if (RegisterClassA(&window_class) == 0)
	{
		return 0;
	}
	int width = 640;
	int height = 480;

	HWND window_handle = CreateWindowA(
		"WindowClass",
		"ウィンドウ生成サンプル",
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME),
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(window_handle, SW_SHOW);

	while (true)
	{
		MSG message;
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
		}
	}
	return 0;
}
