#ifndef CINPUTENGINE_H
#define CINPUTENGINE_H
#include <windows.h>

#ifdef _USRDLL
	#ifdef MTINPUT_EXPORTS
		#define MTINPUT_API __declspec(dllexport)
	#else
		#define MTINPUT_API __declspec(dllimport)
	#endif
#else
#define MTINPUT_API
#endif

#include "base/datatypes.h"
#include "dx9/dinput.h"
#include "utilities/AsyncEvent.h"

class InputEngine;
class InputMouseState;
class InputMouse;
class InputKeyboardState;
class InputKeyboard;
class InputDevice;

#include "input/InputDevice.h"
#include "input/InputKeyboardState.h"
#include "input/InputKeyboard.h"
#include "input/InputMouseState.h"
#include "input/InputMouse.h"

class MTINPUT_API InputEngine
{
protected : u32 threadFrequency;
			u32 threadPriority;
			IDirectInput8* directInput;
			HINSTANCE appInstance;
			HWND wndHandle;
public    : InputEngine();
			virtual ~InputEngine(void);
			virtual void start();
			virtual void stop();
			virtual bit init(HINSTANCE hInstance,HWND hWnd,u32 freq,u32 priority=THREAD_PRIORITY_NORMAL);

			InputKeyboard keyboard;
			InputMouse mouse;		
};

#endif;









