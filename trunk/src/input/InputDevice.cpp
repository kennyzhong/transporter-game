#include "input/InputEngine.h"

//........................................................................................

void InputDevice::start()
{
	if(!isDeviceInited)
	{
		reInit();
	}
	if(isDeviceInited && deviceThreadSignal)
	{
		SetEvent(deviceThreadSignal);
	}	
}

//........................................................................................

void InputDevice::stop( void )
{
	if(isDeviceInited && isThreadRunning)
	{
		isThreadRunning = false;
		SetEvent(deviceThreadSignal);
		if(WaitForSingleObject(deviceThread,1000) == WAIT_TIMEOUT)
		{
			TerminateThread(deviceThread,1);
		}
		destroyDevice();
		deviceHandle = NULL;
		deviceThread = NULL;
		CloseHandle(deviceThreadSignal);
		deviceThreadSignal = NULL;
		CloseHandle(deviceInitSignal);
		deviceInitSignal = NULL;
		isDeviceInited = false;
	}
}

//........................................................................................

bit InputDevice::init( InputEngine* engine, HINSTANCE hInstance,HWND hWnd,
					  IDirectInput8* directInput,u32 freq,u32 priority)
{
	if(!isThreadRunning)
	{
		this->engine = engine;
		this->appInstance = hInstance;
		this->windowHandle = hWnd;
		this->directInputInterface = directInput;
		this->threadFrequency = freq;
		this->threadPriority = priority;
		return reInit();
	}
	return true;
}

//........................................................................................

DWORD WINAPI InputDevice::deviceThreadProc( LPVOID params )
{
	InputDevice* This = (InputDevice*)params;
	try
	{
		This->isDeviceInited = This->initDevice( This->appInstance,This->windowHandle,
			                                     This->directInputInterface,
												 &This->deviceHandle);
	}
	catch (...)
	{
		SetEvent(This->deviceInitSignal);
	}
	SetEvent(This->deviceInitSignal);

	while(This->isThreadRunning)
	{
		if( WaitForSingleObject(This->deviceThreadSignal,INFINITE) == WAIT_OBJECT_0 && 
			This->isThreadRunning )
		{
			This->update();			
			Sleep(1000/This->threadFrequency);
		}
	}
	return 0;
}

//........................................................................................

bit InputDevice::reInit()
{
	if(isThreadRunning)
	{
		stop();
	}
	if(deviceThreadSignal)
	{
		CloseHandle(deviceThreadSignal);
		deviceThreadSignal = NULL;
	}
	if(deviceInitSignal)
	{
		CloseHandle(deviceInitSignal);
		deviceInitSignal = NULL;
	}
	deviceThreadSignal = CreateEvent(NULL,TRUE,FALSE,NULL);
	deviceInitSignal = CreateEvent(NULL,TRUE,FALSE,NULL);
	if(deviceThreadSignal && deviceInitSignal)
	{
		isThreadRunning = true;
		deviceThread = CreateThread(NULL,0,deviceThreadProc,this,0,NULL);
		if(deviceThread)
		{
			SetThreadPriority(deviceThread,threadPriority);
			WaitForSingleObject(deviceInitSignal,INFINITE);
			return isDeviceInited;
		}
	}
	return false;
}

//........................................................................................

InputDevice::InputDevice( str name )
{
	this->engine = NULL;
	this->name = name;
	this->directInputInterface = NULL;
	this->deviceHandle = NULL;
	this->isThreadRunning = false;
	this->isDeviceInited = false;
	this->deviceThreadSignal = NULL;
	this->deviceInitSignal = NULL;
}

//........................................................................................

InputDevice::~InputDevice()
{
	stop();
}
//........................................................................................
