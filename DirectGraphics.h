#ifndef DIRECT_GRAPHICS_H
#define DIRECT_GRAPHICS_H

#include <d3d9.h>
#include <d3dx9.h>

bool InitDirectGraphics(HWND window_handle);

void ReleaseDirectGraphics();
void StartDrawing();
void FinishDrawing();
void DrawPorigon();
void DrawporigonWithTriangleList();
void DrawporigonWithTriangleStrip();
void DrawporigonWithTriangleFan();

struct CustomVertex
{
	float x;
	float y;
	float z;
	float rhw;
	DWORD Color;
};

#endif


