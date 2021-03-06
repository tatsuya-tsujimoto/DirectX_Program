#ifndef INPUT_H
#define INPUT_H

#include <dinput.h>


bool InitDirectInput();
void ReleaseDirectInput();
void UpdateDirectInput();
bool IsKeyHeld(int key);
bool IsKeyPushed(int key);
bool IsKeyReleased(int key);

enum InputState
{
	None,		// 押されてない
	Pushed,		// 押された
	Held,		// 押している
	Released,	// 離した
};
#endif


