#ifndef CINPUTMOUSE_H
#define CINPUTMOUSE_H
#include "input/InputEngine.h"

class MTINPUT_API InputMouse : public InputDevice
{
friend class InputEngine;
protected : bit initDevice(HINSTANCE hInstance,HWND hWnd,
				IN IDirectInput8* directInput,OUT IDirectInputDevice8** device);
			void destroyDevice();
public    : InputMouse();
			~InputMouse();
			void update();
			InputMouseState state;

			AsyncEvent<u32> onMouseBtnDown;
			AsyncEvent<u32> onMouseBtnUp;
			AsyncEvent<u32> onMouseBtnClick;
			AsyncEvent<u32> onMouseBtnDblClick;
			AsyncEvent<i32> onMouseScroll;
			AsyncEvent2<i32,i32> onMouseMove;
};

#endif
