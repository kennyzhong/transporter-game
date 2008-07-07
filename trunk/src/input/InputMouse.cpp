#include "input/InputEngine.h"

//........................................................................................

InputMouse::InputMouse()
: InputDevice("InputMouse")
{

}

//........................................................................................

InputMouse::~InputMouse()
{

}

//........................................................................................

void InputMouse::destroyDevice()
{
	if(deviceHandle)
	{
		deviceHandle->Unacquire(); 
		deviceHandle->Release();
		deviceHandle = NULL;
	}
}

//........................................................................................

bit InputMouse::initDevice( HINSTANCE hInstance,HWND hWnd, IN IDirectInput8* directInput,
						    OUT IDirectInputDevice8** device )
{
	if (FAILED(directInput->CreateDevice(GUID_SysMouse, device, NULL)) )
	{
		return false;
	}

	if (FAILED((*device)->SetDataFormat(&c_dfDIMouse)) )
	{
		return false;
	}

	if (FAILED((*device)->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)) )
	{
		return false;
	}

	DIPROPDWORD diProp;
	diProp.diph.dwSize       = sizeof(DIPROPDWORD);
	diProp.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diProp.diph.dwObj        = 0;
	diProp.diph.dwHow        = DIPH_DEVICE;
	diProp.dwData            = DEF_MOUSE_BUFFER_SIZE;

	if (FAILED((*device)->SetProperty(DIPROP_BUFFERSIZE, &diProp.diph)) )
	{
		return false;
	}
	return true;
}

//........................................................................................

void InputMouse::update()
{
	state.reset();
	DWORD elements = DEF_MOUSE_BUFFER_SIZE;
	HRESULT hr = deviceHandle->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),
		                                     state.inputDeviceData,&elements, 0);
	if( hr != DI_OK ) 
	{
		hr = deviceHandle->Acquire();
		if( hr == DIERR_INPUTLOST || hr == DIERR_OTHERAPPHASPRIO || hr == DIERR_NOTACQUIRED) 
		{
			return;
		}
	}	

	i32 xMovement = 0,
		yMovement = 0,
		zMovement = 0;

	for (u32 ctr = 0; ctr < DEF_MOUSE_BUFFER_SIZE; ctr++)
	{	
		if (!( (state.inputDeviceData[ctr].dwOfs  == 0) && 
			   (state.inputDeviceData[ctr].dwData == 0)  ))
		{
			switch(state.inputDeviceData[ctr].dwOfs)
			{
			case DIMOFS_X      : xMovement += state.inputDeviceData[ctr].dwData; break;
			case DIMOFS_Y      : yMovement += state.inputDeviceData[ctr].dwData; break;
			case DIMOFS_Z      : zMovement += state.inputDeviceData[ctr].dwData; break;
			case DIMOFS_BUTTON0:
			case DIMOFS_BUTTON1:
			case DIMOFS_BUTTON2:
			case DIMOFS_BUTTON3:
			case DIMOFS_BUTTON4:
			case DIMOFS_BUTTON5:
			case DIMOFS_BUTTON6:
			case DIMOFS_BUTTON7:  
				u32 currentTick = GetTickCount();
				u32 button = state.inputDeviceData[ctr].dwOfs - DIMOFS_BUTTON0;
				if(state.inputDeviceData[ctr].dwData & 0x80)
				{			
					state.btnState[button] = true;
					state.btnDownTimestamp[ctr] = currentTick;
					onMouseBtnDown(button);
				}
				else
				{
					state.btnUpTimestamp[ctr] = currentTick;
					if( currentTick - state.btnDownTimestamp[ctr] < DEF_MOUSE_CLICK_THRESHOLD )
					{		
						u32 lastbtnclick = state.btnClickTimestamp[ctr];
						state.btnClickTimestamp[ctr] = currentTick;						 
						if( currentTick - lastbtnclick < DEF_MOUSE_CLICK_THRESHOLD)
						{
							onMouseBtnDblClick(button);
						}
						onMouseBtnClick(button);
					}				
					state.btnState[button] = false;
					onMouseBtnUp(button);
				}			
			}
		}
	}

	if (xMovement || yMovement)
	{
		onMouseMove(i32(xMovement),i32(yMovement));
	}
	if (zMovement)
	{
		onMouseScroll(i32(zMovement));
	}
}