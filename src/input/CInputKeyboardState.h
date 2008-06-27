#ifndef INPUTKEYBOARDSTATE_H
#define INPUTKEYBOARDSTATE_H
#include "input/CInputEngine.h"

class MTINPUT_API CInputKeyboardState
{
friend class CInputKeyboard;
private :u32 _keydowntimestamp[256];
		 u32 _keyuptimestamp[256];
		 u8 _keybuffer[2][256];
		 u8* _keycurrentbuffer;
		 u8* _keylastbuffer;
		 CInputKeyboardState(void);
public : bit is_keydown(u32 button);
		 u32 keydown_timestamp(u32 button);
		 u32 keyup_timestamp(u32 button);
};

#endif