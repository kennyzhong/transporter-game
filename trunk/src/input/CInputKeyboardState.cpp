#include "input/CInputEngine.h"

CInputKeyboardState::CInputKeyboardState(void)
{
	ZeroMemory(_keybuffer,sizeof(u8)*2*256);
	ZeroMemory(_keydowntimestamp,sizeof(u32)*256);
	ZeroMemory(_keyuptimestamp,sizeof(u32)*256);

	_keycurrentbuffer = _keybuffer[0];
	_keylastbuffer    = _keybuffer[1];
}

bit CInputKeyboardState::is_keydown(u32 button)
{
	if(button > 255)
	{
		return false;
	}
	return (_keycurrentbuffer[button] & 0x80)?true:false;
}

u32 CInputKeyboardState::keydown_timestamp(u32 button)
{
	if(button > 255)
	{
		return 0;
	}
	return _keydowntimestamp[button];
}

u32 CInputKeyboardState::keyup_timestamp(u32 button)
{
	if(button > 255)
	{
		return 0;
	}
	return _keyuptimestamp[button];
}