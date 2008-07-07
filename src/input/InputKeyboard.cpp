#include "input/InputEngine.h"

//........................................................................................

bit InputKeyboard::initDevice( HINSTANCE hInstance,HWND hWnd,
						IN IDirectInput8* directInput,OUT IDirectInputDevice8** device )
{
	if(FAILED(directInput->CreateDevice(GUID_SysKeyboard,device, NULL)) )
	{
		return false;
	}

	if(FAILED((*device)->SetDataFormat(&c_dfDIKeyboard)) )
	{
		return false;
	}

	if(FAILED((*device)->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)) )
	{
		return false;
	}
	return true;
}

//........................................................................................

void InputKeyboard::update()
{
	static HRESULT hr;

	if( hr != DI_OK ) 
	{
		hr = deviceHandle->Acquire();
		return;
	}

	u8* temp		       = state.keycurrentBuffer;
	state.keycurrentBuffer = state.keylastBuffer;
	state.keylastBuffer    = temp;

	hr = deviceHandle->GetDeviceState(sizeof(u8)*256,(void*)state.keycurrentBuffer);
	//if(memcmp(state.keycurrentBuffer,state.keylastBuffer,sizeof(u8)*256) != 0)
	//{
		for(u32 ctr = 0; ctr < 256; ctr++)
		{
			if( state.keycurrentBuffer[ctr] != state.keylastBuffer[ctr] )
			{
				u32 currentTick = GetTickCount();
				if( state.keycurrentBuffer[ctr] & 0x80 )
				{				
					state.keydownTimestamp[ctr] = currentTick;
					onKeyDown(ctr);
				}
				else
				{					
					state.keyupTimestamp[ctr] = currentTick;
					if( (currentTick - state.keyupTimestamp[ctr] < KEYPRESS_THRESHOLD))
					{	
						onKeyPress(ctr);
					}
					onKeyUp(ctr);
				}
			}
		}
	//}
}

//........................................................................................

InputKeyboard::InputKeyboard() 
: InputDevice("InputKeyboard")
{

}

//........................................................................................

InputKeyboard::~InputKeyboard()
{

}

//........................................................................................

void InputKeyboard::destroyDevice()
{
	if(deviceHandle)
	{
		deviceHandle->Unacquire(); 
		deviceHandle->Release();
		deviceHandle = NULL;
	}
}