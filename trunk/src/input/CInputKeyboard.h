#ifndef CINPUTKEYBOARD_H
#define CINPUTKEYBOARD_H
#define KEYPRESS_THRESHOLD 500
#include "input/CInputEngine.h"

class MTINPUT_API CInputKeyboard : public CInputDevice
{
	friend class CInputManager;
	protected : CInputKeyboardState* _state;
				CInputKeyboard(CInputManager* parent);
				~CInputKeyboard(void);	
				bit init(HINSTANCE hInstance,HWND hWnd,IDirectInput8* DirectInput);				
	public    : void update(void);
				CInputKeyboardState* get_state(void);
};

#endif