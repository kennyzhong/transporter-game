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
#include "base/CBaseObject.h"
#include "utilities/objectvector.h"
#include "utilities/Event.h"
#include "dx9/dinput.h"

class CInputEngine;
class CInputState;
class CInputManager;
class CInputMouseState;
class CInputMouse;
class CInputKeyboardState;
class CInputKeyboard;
class CInputEventObject;
class CInputEventTrigger;
class CInputMap;
class CInputDevice;

#include "input/CInputEventObject.h"
#include "input/CInputEvent.h"
#include "input/CInputMap.h"
#include "input/CInputDevice.h"
#include "input/CInputKeyboardState.h"
#include "input/CInputKeyboard.h"
#include "input/CInputMouseState.h"
#include "input/CInputMouse.h"
#include "input/CInputManager.h"

class MTINPUT_API CInputEngine : public CBaseObject
{
	protected : CInputManager* _input_manager;
				u32 _freq;
				u32 _priority;
	public    : CInputEngine(HINSTANCE hInstance,HWND hWnd);
				~CInputEngine(void);
				CInputManager* get_input_manager(void);	

				void start(u32 freq,u32 priority=THREAD_PRIORITY_NORMAL);
				void stop(void);

				u32 get_thread_freq(void);
				u32 get_thread_priority(void);
};

#endif;









