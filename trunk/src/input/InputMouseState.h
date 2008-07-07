#ifndef INPUTMOUSESTATE_H
#define INPUTMOUSESTATE_H
#include "input/InputEngine.h"

#define DEF_MOUSE_BUFFER_SIZE 64
#define DEF_MOUSE_BTN_COUNT 8
#define DEF_MOUSE_CLICK_THRESHOLD 500

class MTINPUT_API InputMouseState
{
friend class InputMouse;
protected : DIDEVICEOBJECTDATA* inputDeviceData;
			u32 inputBufferSize;
			bit btnState[DEF_MOUSE_BTN_COUNT];
			u32 btnDownTimestamp[DEF_MOUSE_BTN_COUNT];
			u32 btnUpTimestamp[DEF_MOUSE_BTN_COUNT];
			u32 btnClickTimestamp[DEF_MOUSE_BTN_COUNT];
			InputMouseState();
			~InputMouseState();
public    : bit isBtnDown(u32 btn);
			void getMovement(OUT i32& x,OUT i32& y,OUT i32& z);
			u32 getBtnDownTimestamp(u32 btn);
			u32 getBtnUpTimestamp(u32 btn);
			u32 getBtnClickTimestamp(u32 btn);
			void reset(void);
};

#endif