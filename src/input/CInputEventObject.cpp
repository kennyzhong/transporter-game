#include "input/CInputEngine.h"

CInputEventObject::CInputEventObject(str eventname,CBaseObject* parent)
:CBaseObject(eventname,parent)
{
	_runthread = true;
	_eventsignal = CreateEvent(NULL,FALSE,FALSE,NULL);
	_eventthread = CreateThread(NULL,0,_eventthread_proc,this,0,NULL);
}

CInputEventObject::~CInputEventObject(void)
{
	_runthread = false;
	SetEvent(_eventsignal);
	u32 waitresult = WaitForSingleObject(_eventthread,1000);
	if(waitresult == WAIT_TIMEOUT)
	{
		TerminateThread(_eventthread,1);
	}
	CloseHandle(_eventsignal);
	_eventsignal = INVALID_HANDLE_VALUE;
	_eventthread = INVALID_HANDLE_VALUE;
}

DWORD WINAPI CInputEventObject::_eventthread_proc(LPVOID param)
{
	CInputEventObject* This = (CInputEventObject*)param;
	while(This->_runthread)
	{
		u32 waitresult = WaitForSingleObject(This->_eventsignal,INFINITE);
		if(waitresult == WAIT_OBJECT_0 && This->_runthread)
		{
			This->call();
		}
	}				
	return 0;
}