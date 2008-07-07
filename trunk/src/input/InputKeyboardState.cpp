#include "input/InputEngine.h"

InputKeyboardState::InputKeyboardState()
{
	ZeroMemory(keybuffer,sizeof(u8)*2*256);
	ZeroMemory(keydownTimestamp,sizeof(u32)*256);
	ZeroMemory(keyupTimestamp,sizeof(u32)*256);

	keycurrentBuffer = keybuffer[0];
	keylastBuffer    = keybuffer[1];
}

InputKeyboardState::~InputKeyboardState()
{

}

bit InputKeyboardState::isKeyDown( u32 button )
{
	if(button > 255)
	{
		return false;
	}
	return (keycurrentBuffer[button] & 0x80)?true:false;
}

u32 InputKeyboardState::getKeyDownTimestamp( u32 button )
{
	if(button > 255)
	{
		return 0;
	}
	return keydownTimestamp[button];
}

u32 InputKeyboardState::getkeyUpTimestamp( u32 button )
{
	if(button > 255)
	{
		return 0;
	}
	return keyupTimestamp[button];
}