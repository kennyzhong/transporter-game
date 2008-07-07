#include "input/InputEngine.h"

//........................................................................................

InputMouseState::InputMouseState()
{
	inputBufferSize = DEF_MOUSE_BUFFER_SIZE;
	inputDeviceData = new DIDEVICEOBJECTDATA[inputBufferSize];
	ZeroMemory(&btnState,sizeof(bit)*DEF_MOUSE_BTN_COUNT);
	ZeroMemory(inputDeviceData, sizeof(DIDEVICEOBJECTDATA)*DEF_MOUSE_BUFFER_SIZE);
}

//........................................................................................

InputMouseState::~InputMouseState()
{
	if( inputDeviceData )
	{
		delete[] inputDeviceData;
		inputDeviceData = NULL;
	}
	inputBufferSize = 0;
}

//........................................................................................

bit InputMouseState::isBtnDown( u32 btn )
{
	if(btn < DEF_MOUSE_BTN_COUNT)
	{
		return btnState[btn];
	}
	return false;
}

//........................................................................................

void InputMouseState::getMovement( OUT i32& x,OUT i32& y,OUT i32& z )
{
	x = y = z = 0;

	for (u32 elements = 0; elements < inputBufferSize; elements++)
	{
		if( DIMOFS_X == inputDeviceData[elements].dwOfs )
		{
			x += inputDeviceData[elements].dwData;
		}	
		else if( DIMOFS_Y == inputDeviceData[elements].dwOfs )
		{
			y += inputDeviceData[elements].dwData;
		}
		else if( DIMOFS_Y == inputDeviceData[elements].dwOfs )
		{
			z += inputDeviceData[elements].dwData;
		}
	}
}

//........................................................................................

u32 InputMouseState::getBtnDownTimestamp( u32 btn )
{
	if(btn < DEF_MOUSE_BTN_COUNT)
	{
		return btnDownTimestamp[btn];
	}
	return 0;
}

//........................................................................................

u32 InputMouseState::getBtnUpTimestamp( u32 btn )
{
	if(btn < DEF_MOUSE_BTN_COUNT)
	{
		return btnUpTimestamp[btn];
	}
	return 0;
}

//........................................................................................

u32 InputMouseState::getBtnClickTimestamp( u32 btn )
{
	if(btn < DEF_MOUSE_BTN_COUNT)
	{
		return btnClickTimestamp[btn];
	}
	return 0;
}

//........................................................................................

void InputMouseState::reset( void )
{
	ZeroMemory(inputDeviceData, sizeof(DIDEVICEOBJECTDATA)*DEF_MOUSE_BUFFER_SIZE);
}