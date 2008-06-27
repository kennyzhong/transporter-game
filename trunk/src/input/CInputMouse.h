#ifndef CINPUTMOUSE_H
#define CINPUTMOUSE_H
#include "input/CInputEngine.h"

class MTINPUT_API CInputMouse : public CInputDevice
{
	friend class CInputManager;
	protected : u32 _InputBufferSize;
				CInputMouseState* _state;
				bit init(HINSTANCE hInstance,HWND hWnd,IDirectInput8* DirectInput);
				CInputMouse(CInputManager* parent);
				~CInputMouse(void);
	public    : void update(void);

				bit get_button_state(u32 btn);
				void set_buffer_size(u32 size);
				u32 get_buffer_size(void);
				void set_cooperative_level(u32 level);
				u32 get_cooperative_level(void);
				void get_movement(OUT i32& x,OUT i32& y,OUT i32& z);

				CInputMouseState* get_state(void);
};

#endif
