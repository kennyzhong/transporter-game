#include "input/InputEngine.h"

#ifdef _USRDLL
BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
#endif

//........................................................................................

InputEngine::InputEngine()
{
	this->threadFrequency = 60;
	this->threadPriority = THREAD_PRIORITY_NORMAL;
	this->directInput = NULL;
}

//........................................................................................

InputEngine::~InputEngine( void )
{
	stop();
	if(directInput)
	{
		directInput->Release();
		directInput = NULL;
	}
}

//........................................................................................

bit InputEngine::init( HINSTANCE hInstance,HWND hWnd,u32 freq,u32 priority )
{
	this->appInstance = hInstance;
	this->wndHandle = hWnd;
	this->threadFrequency = freq;
	this->threadPriority = priority;
	bit result = true;

	if (FAILED (DirectInput8Create(appInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**) &directInput, NULL)))
	{
		result = false;
	}
	if(result)
	{
		result &= mouse.init(this,appInstance,wndHandle,directInput,threadFrequency,threadPriority);
		result &= keyboard.init(this,appInstance,wndHandle,directInput,threadFrequency,threadPriority);
		//result &= mouse.init(this,appInstance,wndHandle,directInput,15,THREAD_PRIORITY_LOWEST);
		//result &= keyboard.init(this,appInstance,wndHandle,directInput,15,THREAD_PRIORITY_LOWEST);
	}
	return result;
}

//........................................................................................

void InputEngine::start()
{
	mouse.start();
	keyboard.start();
}

//........................................................................................

void InputEngine::stop()
{
	mouse.stop();
	keyboard.stop();
}