#ifndef DIRECT_GRAPHICS_H
#define DIRECT_GRAPHICS_H


#include <d3d9.h>
#include <d3dx9.h>



enum TextureID
{
	Tex1,
	tex2,
	TexIDMax,
};


bool InitDirectGraphics(HWND window_handle);

void ReleaseDirectGraphics();
void StartDrawing();
void FinishDrawing();
void DrawPorigon();
void DrawporigonWithTrinangleList();
void DrawPorigonWithTriangleStrip();
void DrawPorigonWithTriangleFan(TextureID tex_id);

void SetUpView();
void SetUpProjection();
void UpdateCamera(float rotate, float go, float slide);

void Draw3DPorigon();

void DrawXFile(float rotate, float go, float slide);

bool LoadXFile(LPCWSTR file_name);
bool LoadTexture(TextureID tex_id);

void ReleaseTexture();
void ReleaseXFile();

struct CustomVertex
{
	float x;
	float y;
	float z;
	float rhw;
	DWORD Color;
};


struct CustomVertexTex
{
	float x;
	float y;
	float z;
	float rhw;
	DWORD Color;
	float TU;
	float TV;
};

// 3D用の頂点構造
struct CustomVertex3D
{
	float x;
	float y;
	float z;

	// 頂点カラー
	DWORD Color;


};

#define FVF_2D_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
#define FVF_2D_VERTEX_TEXTURE (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
// FVF設定(3D用)
#define FVF_3D_VERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

#endif


