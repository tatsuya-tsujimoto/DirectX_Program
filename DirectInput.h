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
	None,		// ‰Ÿ‚³‚ê‚Ä‚È‚¢
	Pushed,		// ‰Ÿ‚³‚ê‚½
	Held,		// ‰Ÿ‚µ‚Ä‚¢‚é
	Released,	// —£‚µ‚½
};
#endif


