#include"DirectGraphics.h"

LPDIRECT3D9 g_Interface = nullptr;
LPDIRECT3DDEVICE9 g_Device = nullptr;

bool InitDirectGraphics(HWND window_handle)
{

	g_Interface = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_Interface == nullptr)
	{
		return false;
	}
	D3DPRESENT_PARAMETERS parameters;

	ZeroMemory(&parameters, sizeof(D3DPRESENT_PARAMETERS));

	parameters.BackBufferCount = 1;

	parameters.BackBufferFormat = D3DFMT_UNKNOWN;

	parameters.Windowed = true;

	parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;

	HRESULT result = g_Interface->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,

		&parameters,
		&g_Device
	);

	/*


	*/
	if (FAILED(result))
	{
		return false;
	}

	return true;




}

void ReleaseDirectGraphics()
{
	if (g_Device != nullptr)
	{
		g_Device->Release();
		g_Device = nullptr;
	}

	if (g_Interface != nullptr)
	{

		g_Interface->Release();
		g_Interface = nullptr;
	}
}

void StartDrawing()
{
	g_Device->Clear(
		0,
		nullptr,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f,
		0
	);
	g_Device->BeginScene();
}

void FinishDrawing()
{
	g_Device->EndScene();
	g_Device->Present(nullptr, nullptr, nullptr, nullptr);
}

void DrawPorigon()
{
	CustomVertex vertices[] =
	{
		{0.0f  ,50.0f ,0.0f,1.0f,0xffffff},
		{500.0f,300.0f,0.0f,1.0f,0xffffff},
		{50.0f ,300.0f,0.0f,1.0f,0xffffff},
	};
	g_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	g_Device->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		1,
		vertices,
		sizeof(CustomVertex)
	);
}

void DrawporigonWithTriangleList()
{
	CustomVertex vertices[] =
	{
		{0.0f  ,0.0f  ,0.0f,1.0f,0xffffff},
		{100.0f,0.0f  ,0.0f,1.0f,0xffffff},
		{0.0f  ,100.0f,0.0f,1.0f,0xffffff},
		{100.0f,0.0f  ,0.0f,1.0f,0xffffff},
		{100.0f,100.0f,0.0f,1.0f,0xffffff},
		{0.0f  ,100.0f,0.0f,1.0f,0xffffff},
	};
	g_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	g_Device->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		2,
		vertices,
		sizeof(CustomVertex)
	);
}

void DrawporigonWithTriangleStrip()
{
	CustomVertex vertices[] =
	{
		{300.0f,0.0f  ,0.0f,1.0f,0xffffff},
		{350.0f,0.0f  ,0.0f,1.0f,0xffffff},
		{300.0f,200.0f,0.0f,1.0f,0xffffff},
		{350.0f,200.0f,0.0f,1.0f,0xffffff},
	};
	g_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	g_Device->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,
		2,
		vertices,
		sizeof(CustomVertex)
	);
}

void DrawporigonWithTriangleFan()
{
	CustomVertex vertices[] =
	{
		{300.0f,100.0f,0.0f,1.0f,0xffffff},
		{300.0f,100.0f,0.0f,1.0f,0xffffff},
		{300.0f,200.0f,0.0f,1.0f,0xffffff},
		{200.0f,200.0f,0.0f,1.0f,0xffffff},
	};
	g_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	g_Device->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		vertices,
		sizeof(CustomVertex)
	);
}