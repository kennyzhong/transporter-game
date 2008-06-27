#include "input/CInputEngine.h"

CInputKeyboard::CInputKeyboard(CInputManager* parent)
:CInputDevice("input_keyboard",parent)
{
	_InputDevice = NULL;
	_state = new CInputKeyboardState;
}

//........................................................................................

CInputKeyboard::~CInputKeyboard(void)
{
	if( _state )
	{
		delete _state;
		_state = NULL;
	}
}

//........................................................................................

bit CInputKeyboard::init(HINSTANCE hInstance,HWND hWnd,IDirectInput8* DirectInput)
{
	if(FAILED(DirectInput->CreateDevice(GUID_SysKeyboard,&_InputDevice, NULL)) )
	{
		return false;
	}

	if(FAILED(_InputDevice->SetDataFormat(&c_dfDIKeyboard)) )
	{
		return false;
	}

	if(FAILED(_InputDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)) )
	{
		return false;
	}
	return true;
}

//........................................................................................

void CInputKeyboard::update(void)
{
	if(!_active_map)
	{
		return;
	}
	static HRESULT hr = DI_OK;

	if( hr != DI_OK ) 
	{
		hr = _InputDevice->Acquire();
		return;
	}

	u8* temp		          = _state->_keycurrentbuffer;
	_state->_keycurrentbuffer = _state->_keylastbuffer;
	_state->_keylastbuffer    = temp;

	hr = _InputDevice->GetDeviceState(sizeof(u8)*256,(void*)_state->_keycurrentbuffer);

	for(u32 ctr = 0; ctr < 256; ctr++)
	{
		if( _state->_keycurrentbuffer[ctr] != _state->_keylastbuffer[ctr] )
		{
			u32 currentTick = GetTickCount();
			if( _state->_keycurrentbuffer[ctr] & 0x80 )
			{				
				_state->_keydowntimestamp[ctr] = currentTick;
				if(_active_map)
				{
					_active_map->trigger->KeyDown(ctr);
				}
			}
			else
			{					
				_state->_keyuptimestamp[ctr] = currentTick;
				if( (currentTick - _state->_keydowntimestamp[ctr] < KEYPRESS_THRESHOLD) && 
					 _active_map)
				{	
					_active_map->trigger->KeyPress(ctr);
				}
				if(_active_map)
				{
					_active_map->trigger->KeyUp(ctr);
				}
			}
		}
	}
}

//........................................................................................

CInputKeyboardState* CInputKeyboard::get_state(void)
{ 
	return _state; 
}