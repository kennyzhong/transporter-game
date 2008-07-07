#ifndef INPUTKEYBOARDSTATE_H
#define INPUTKEYBOARDSTATE_H
#include "input/InputEngine.h"

class MTINPUT_API InputKeyboardState
{
friend class InputKeyboard;
protected :u32 keydownTimestamp[256];
		   u32 keyupTimestamp[256];
		   u8  keybuffer[2][256];
		   u8* keycurrentBuffer;
		   u8* keylastBuffer;
		   InputKeyboardState();
		   ~InputKeyboardState();
public   : bit isKeyDown(u32 button);
		   u32 getKeyDownTimestamp(u32 button);
		   u32 getkeyUpTimestamp(u32 button);
};

#endif