#ifndef CINPUTKEYBOARD_H
#define CINPUTKEYBOARD_H
#define KEYPRESS_THRESHOLD 500
#include "input/InputEngine.h"

class MTINPUT_API InputKeyboard : public InputDevice
{
friend class InputEngine;
protected : bit initDevice(HINSTANCE hInstance,HWND hWnd,
				     IN IDirectInput8* directInput,OUT IDirectInputDevice8** device);
			void destroyDevice();
public    : InputKeyboard();
			~InputKeyboard();
			void update();
		    InputKeyboardState state;

		    AsyncEvent<u32> onKeyDown;
		    AsyncEvent<u32> onKeyUp;
		    AsyncEvent<u32> onKeyPress;
};

#endif