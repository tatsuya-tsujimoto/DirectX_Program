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
	None,		// ������ĂȂ�
	Pushed,		// �����ꂽ
	Held,		// �����Ă���
	Released,	// ������
};
#endif


