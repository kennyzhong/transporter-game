#ifndef INPUTMOUSESTATE_H
#define INPUTMOUSESTATE_H
#include "input/CInputEngine.h"

#define DEF_MOUSE_BUFFER_SIZE 64
#define DEF_MOUSE_BTN_COUNT 8
#define DEF_MOUSE_CLICK_THRESHOLD 500

class MTINPUT_API CInputMouseState
{
friend class CInputMouse;
private : DIDEVICEOBJECTDATA* _InputDeviceData;
		  IDirectInputDevice8** _InputDevice;
		  u32 _InputBufferSize;
		  u32 _btndowntimestamp[DEF_MOUSE_BTN_COUNT];
		  u32 _btnuptimestamp[DEF_MOUSE_BTN_COUNT];
		  u32 _btnclicktimestamp[DEF_MOUSE_BTN_COUNT];
		  CInputMouseState(u32 buffersize,IDirectInputDevice8** mouse);
		  ~CInputMouseState(void);
public  : bit is_btndown(u32 btn);
		  void get_movement(OUT i32& x,OUT i32& y,OUT i32& z);
		  u32 btndown_timestamp(u32 btn);
		  u32 btnup_timestamp(u32 btn);
		  u32 btnclick_timestamp(u32 btn);
		  void reset(void);
};

#endif