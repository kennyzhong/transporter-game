#ifndef INPUTEVENTOBJECT_H
#define INPUTEVENTOBJECT_H
#include "input/CInputEngine.h"

class CInputEventObject : public CBaseObject
{
friend DWORD WINAPI CInputEventObject::_eventthread_proc(LPVOID param);
protected : HANDLE _eventsignal;
			HANDLE _eventthread;
			bit _runthread;
			static DWORD WINAPI _eventthread_proc(LPVOID param);
			CInputEventObject(str eventname,CBaseObject* parent);
			~CInputEventObject(void);
			virtual void call(void) = 0;		
};
#endif