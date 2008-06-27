#include "input/CInputEngine.h"

CInputMouse::CInputMouse(CInputManager* parent)
:CInputDevice("input_mouse",parent)
{
	_InputBufferSize = DEF_MOUSE_BUFFER_SIZE;
	_state = new CInputMouseState(_InputBufferSize,&_InputDevice);
}

//........................................................................................

CInputMouse::~CInputMouse(void)
{
	if(_state)
	{
		delete _state;
		_state = NULL;
	}
}

//........................................................................................

bit CInputMouse::init(HINSTANCE hInstance,HWND hWnd,IDirectInput8* DirectInput)
{
	if (FAILED(DirectInput->CreateDevice(GUID_SysMouse, &_InputDevice, NULL)) )
	{
		return false;
	}

	if (FAILED(_InputDevice->SetDataFormat(&c_dfDIMouse)) )
	{
		return false;
	}

	if (FAILED(_InputDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)) )
	{
		return false;
	}

	DIPROPDWORD diProp;
	diProp.diph.dwSize       = sizeof(DIPROPDWORD);
	diProp.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diProp.diph.dwObj        = 0;
	diProp.diph.dwHow        = DIPH_DEVICE;
	diProp.dwData            = _InputBufferSize;

	if (FAILED(_InputDevice->SetProperty(DIPROP_BUFFERSIZE, &diProp.diph)) )
	{
		return false;
	}
	return true;
}

//........................................................................................

void CInputMouse::update(void)
{
	if(!_active_map)
	{
		return;
	}	
	_state->reset();
	DWORD elements = _InputBufferSize;
	HRESULT hr = _InputDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),
		                                     _state->_InputDeviceData,&elements, 0);
	if( hr != DI_OK ) 
	{
		hr = _InputDevice->Acquire();
		if( hr == DIERR_INPUTLOST || hr == DIERR_OTHERAPPHASPRIO || hr == DIERR_NOTACQUIRED) 
		{
			return;
		}
	}	

	i32 xMovement = 0,
		yMovement = 0,
		zMovement = 0;

	for (u32 ctr = 0; ctr < _InputBufferSize; ctr++)
	{	
		if (!( (_state->_InputDeviceData[ctr].dwOfs == 0) && 
			(_state->_InputDeviceData[ctr].dwData == 0)  ))
		{
			switch(_state->_InputDeviceData[ctr].dwOfs)
			{
			case DIMOFS_X      : xMovement += _state->_InputDeviceData[ctr].dwData; break;
			case DIMOFS_Y      : yMovement += _state->_InputDeviceData[ctr].dwData; break;
			case DIMOFS_Z      : zMovement += _state->_InputDeviceData[ctr].dwData; break;
			case DIMOFS_BUTTON0:
			case DIMOFS_BUTTON1:
			case DIMOFS_BUTTON2:
			case DIMOFS_BUTTON3:
			case DIMOFS_BUTTON4:
			case DIMOFS_BUTTON5:
			case DIMOFS_BUTTON6:
			case DIMOFS_BUTTON7:  
				u32 currentTick = GetTickCount();
				if( _state->_InputDeviceData[ctr].dwData & 0x80)
				{			
					_state->_btndowntimestamp[ctr] = currentTick;
					_active_map->trigger->MouseBtnDown(_state->_InputDeviceData[ctr].dwOfs);
				}
				else
				{
					_state->_btnuptimestamp[ctr] = currentTick;
					if( (currentTick - _state->_btndowntimestamp[ctr] < DEF_MOUSE_CLICK_THRESHOLD) && 
						 _active_map)
					{		
						u32 lastbtnclick = _state->_btnclicktimestamp[ctr];
						_state->_btnclicktimestamp[ctr] = currentTick;						 
						if( (currentTick - lastbtnclick < DEF_MOUSE_CLICK_THRESHOLD) && 
							_active_map)
						{
							_active_map->trigger->MouseBtnDblClick(_state->_InputDeviceData[ctr].dwOfs);
						}
						_active_map->trigger->MouseBtnClick(_state->_InputDeviceData[ctr].dwOfs);
					}				
					_active_map->trigger->MouseBtnUp(_state->_InputDeviceData[ctr].dwOfs);
				}			
				break;
			}
		}
	}

	if (xMovement || yMovement)
	{
		_active_map->trigger->MouseMove(i32(xMovement),i32(yMovement));
	}
	if (zMovement)
	{
		_active_map->trigger->MouseScroll(i32(zMovement));
	}
}

//........................................................................................

void CInputMouse::set_buffer_size(u32 size)
{

}

u32 CInputMouse::get_buffer_size(void)
{ 
	return _InputBufferSize; 
}

void CInputMouse::set_cooperative_level(u32 level)
{

}

u32 CInputMouse::get_cooperative_level(void)
{
	return 0;
}

CInputMouseState* CInputMouse::get_state(void)
{ 
	return _state; 
}

//........................................................................................