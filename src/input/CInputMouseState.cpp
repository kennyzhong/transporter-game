#include "input/CInputEngine.h"

CInputMouseState::CInputMouseState(u32 buffersize,IDirectInputDevice8** mouse)
{
	_InputDevice     = mouse;
	_InputBufferSize = buffersize;
	_InputDeviceData = new DIDEVICEOBJECTDATA[buffersize];
	ZeroMemory(_InputDeviceData, sizeof(DIDEVICEOBJECTDATA)*buffersize);
}

CInputMouseState::~CInputMouseState(void)
{
	if( _InputDeviceData )
	{
		delete[] _InputDeviceData;
		_InputDeviceData = NULL;
	}
	_InputBufferSize = 0;
}

bit CInputMouseState::is_btndown(u32 btn)
{
	if(*_InputDevice)
	{
		DIMOUSESTATE2 state;
		(*_InputDevice)->GetDeviceState(sizeof(DIMOUSESTATE2), &state);
		return (state.rgbButtons[btn] & 0x80)?true:false;
	}
	return false;
}

void CInputMouseState::get_movement(OUT i32& x,OUT i32& y,OUT i32& z)
{
	x = y = z = 0;

	for (u32 elements = 0; elements < _InputBufferSize; elements++)
	{
		if( DIMOFS_X == _InputDeviceData[elements].dwOfs )
		{
			x += _InputDeviceData[elements].dwData;
		}	
		else if( DIMOFS_Y == _InputDeviceData[elements].dwOfs )
		{
			y += _InputDeviceData[elements].dwData;
		}
		else if( DIMOFS_Y == _InputDeviceData[elements].dwOfs )
		{
			z += _InputDeviceData[elements].dwData;
		}
	}
}

u32 CInputMouseState::btndown_timestamp(u32 btn)
{
	if(btn < DEF_MOUSE_BTN_COUNT)
	{
		return _btndowntimestamp[btn];
	}
	return 0;
}

u32 CInputMouseState::btnup_timestamp(u32 btn)
{
	if(btn < DEF_MOUSE_BTN_COUNT)
	{
		return _btnuptimestamp[btn];
	}
	return 0;
}

u32 CInputMouseState::btnclick_timestamp(u32 btn)
{
	if(btn < DEF_MOUSE_BTN_COUNT)
	{
		return _btnclicktimestamp[btn];
	}
	return 0;
}

void CInputMouseState::reset(void)
{
	ZeroMemory(_InputDeviceData, sizeof(DIDEVICEOBJECTDATA) * _InputBufferSize);
}