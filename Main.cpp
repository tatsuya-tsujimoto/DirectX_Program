#include<Windows.h>
#include"DirectGraphics.h"

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

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
		CS_HREDRAW | CS_VREDRAW,			// クラスのスタイル（CS_HREDRAW と　CS_VREDRAW　は横と縦の変更許可設定）
		WindowProcedure,					// ●ウィンドウプロシージャ
		0,									// 補助メモリ
		0,									// 補助メモリ
		hInstance,							// ●このアプリのインスタンスハンドル
		LoadIcon(NULL, IDI_APPLICATION),	// アイコン画像
		LoadCursor(NULL, IDC_ARROW),		// カーソル画像
		nullptr,							// 背景ブラシ(背景色)
		nullptr,							// メニュー名
		TEXT("WindowClass"),				// ●クラス名
	};

	if (RegisterClass(&window_class) == 0)
	{
		return 0;
	}

	int width = 640;
	int height = 480;

	// ウィンドウ作成
	HWND window_handle = CreateWindow(
		// ●登録しているウィンドウクラス構造体の名前
		TEXT("WindowClass"),
		// ●ウィンドウ名(タイトルバーに表示される)
		TEXT("ウィンドウ生成サンプル"),
		// ウィンドウスタイル
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME),
		// ●表示位置
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		// ●サイズ
		width,
		height,
		// 親ハンドル
		NULL,
		// メニューハンドル
		NULL,
		// ●インスタンスハンドル
		hInstance,
		// WM_CREATEメッセージでlpparamに渡したい値
		NULL);

	RECT window_rect;
	if (GetWindowRect(window_handle, &window_rect) == false)
	{//失敗
		return 0;
	}

	RECT client_rect;
	if (GetClientRect(window_handle, &client_rect) == false)
	{
		return 0;
	}
	// フレームサイズの算出
	int frame_size_x = (window_rect.right - window_rect.left) - (client_rect.right - client_rect.left);
	int frame_size_y = (window_rect.bottom - window_rect.top) - (client_rect.bottom - client_rect.top);
	// リサイズの算出
	int resize_width = frame_size_x + width;
	int resize_height = frame_size_y + height;

	// ウィンドウサイズの更新
	SetWindowPos(
		window_handle,// ●
		nullptr,
		// 表示位置
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		// ●リサイズの横幅
		resize_width,
		// ●リサイズの縦幅
		resize_height,
		// オプションの指定
		SWP_NOMOVE
	);
	ShowWindow(window_handle, SW_SHOW);


	if (InitDirectGraphics(window_handle) == false)
	{
		return 0;
	}

	while (true)
	{
		MSG message;
		/*

		if (GetMessage(&message, nullptr, 0, 100))
		{

		}*/

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
			StartDrawing();

			DrawPorigon();
			DrawporigonWithTriangleList();
			DrawporigonWithTriangleStrip();
			DrawporigonWithTriangleFan();

			FinishDrawing();
		}


	}
	ReleaseDirectGraphics();

	return 0;
}