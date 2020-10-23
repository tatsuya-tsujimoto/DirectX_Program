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
		//���͊o���������ǂ�
		CS_HREDRAW | CS_VREDRAW,			// �N���X�̃X�^�C���iCS_HREDRAW �Ɓ@CS_VREDRAW�@�͉��Əc�̕ύX���ݒ�j
		WindowProcedure,					// ���E�B���h�E�v���V�[�W��
		0,									// �⏕������
		0,									// �⏕������
		hInstance,							// �����̃A�v���̃C���X�^���X�n���h��
		LoadIcon(NULL, IDI_APPLICATION),	// �A�C�R���摜
		LoadCursor(NULL, IDC_ARROW),		// �J�[�\���摜
		nullptr,							// �w�i�u���V(�w�i�F)
		nullptr,							// ���j���[��
		TEXT("WindowClass"),				// ���N���X��
	};

	if (RegisterClass(&window_class) == 0)
	{
		return 0;
	}

	int width = 640;
	int height = 480;

	// �E�B���h�E�쐬
	HWND window_handle = CreateWindow(
		// ���o�^���Ă���E�B���h�E�N���X�\���̖̂��O
		TEXT("WindowClass"),
		// ���E�B���h�E��(�^�C�g���o�[�ɕ\�������)
		TEXT("�E�B���h�E�����T���v��"),
		// �E�B���h�E�X�^�C��
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME),
		// ���\���ʒu
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		// ���T�C�Y
		width,
		height,
		// �e�n���h��
		NULL,
		// ���j���[�n���h��
		NULL,
		// ���C���X�^���X�n���h��
		hInstance,
		// WM_CREATE���b�Z�[�W��lpparam�ɓn�������l
		NULL);

	RECT window_rect;
	if (GetWindowRect(window_handle, &window_rect) == false)
	{//���s
		return 0;
	}

	RECT client_rect;
	if (GetClientRect(window_handle, &client_rect) == false)
	{
		return 0;
	}
	// �t���[���T�C�Y�̎Z�o
	int frame_size_x = (window_rect.right - window_rect.left) - (client_rect.right - client_rect.left);
	int frame_size_y = (window_rect.bottom - window_rect.top) - (client_rect.bottom - client_rect.top);
	// ���T�C�Y�̎Z�o
	int resize_width = frame_size_x + width;
	int resize_height = frame_size_y + height;

	// �E�B���h�E�T�C�Y�̍X�V
	SetWindowPos(
		window_handle,// ��
		nullptr,
		// �\���ʒu
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		// �����T�C�Y�̉���
		resize_width,
		// �����T�C�Y�̏c��
		resize_height,
		// �I�v�V�����̎w��
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