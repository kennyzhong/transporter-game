#include "input/CInputEngine.h"

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

CInputEngine::CInputEngine(HINSTANCE hInstance,HWND hWnd)
:CBaseObject("input_engine",NULL)
{
	_input_manager = new CInputManager;
	if( !_input_manager->init(hInstance,hWnd) )
	{
		delete _input_manager;
		_input_manager = NULL;
	}
}

//........................................................................................

CInputEngine::~CInputEngine(void)
{
	if(_input_manager)
	{
		delete _input_manager;
		_input_manager = NULL;
	}
}

//........................................................................................

CInputManager* CInputEngine::get_input_manager(void)
{
	return _input_manager;
}

void CInputEngine::start(u32 freq,u32 priority)
{
	_freq = freq;
	_priority = priority;
	_input_manager->start(freq,priority);
}

void CInputEngine::stop(void)
{
	_input_manager->stop();
}

u32 CInputEngine::get_thread_freq(void)
{ 
	return _freq; 
}

u32 CInputEngine::get_thread_priority(void)
{ 
	return _priority; 
}