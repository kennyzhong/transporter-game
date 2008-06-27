#include "input/CInputEngine.h"

CInputDevice::CInputDevice(str objectname,CInputManager* parent)
:CBaseObject(objectname,parent)
{
	parent->onMapChanged.connect(evMapChanged,this);
	_active_map = NULL;
	_is_device_thread_run = false;
	//_device_event = INVALID_HANDLE_VALUE;
	_device_thread = INVALID_HANDLE_VALUE;
}

//........................................................................................

CInputDevice::~CInputDevice(void)
{
	if(_is_device_thread_run)
	{
		stop();
	}
	CInputManager* parent = (CInputManager*)_owner;
	parent->onMapChanged.disconnect(evMapChanged);
	if(NULL != _InputDevice)
	{		
		_InputDevice->Release();
		_InputDevice = NULL;
	}	
}

//........................................................................................

void CInputDevice::evMapChanged(void* owner,CInputMap* oldmap,CInputMap* newmap)
{
	CInputDevice* This = (CInputDevice*)owner;
	This->changemap(newmap);
}

//........................................................................................

void CInputDevice::changemap(CInputMap* newmap)
{
	_active_map = newmap;
}

//........................................................................................

DWORD WINAPI CInputDevice::_device_thread_proc(LPVOID param)
{
	CInputDevice* This = (CInputDevice*)param;	
	//This->_InputDevice->SetEventNotification(This->_device_event);
	This->_InputDevice->Acquire();
	while(This->_is_device_thread_run)
	{
		HRESULT hr = This->_InputDevice->Poll();
		//if(hr == DIERR_NOTACQUIRED || hr==DIERR_INPUTLOST)
		//{
		//	This->_InputDevice->Acquire();
		//	This->_InputDevice->Poll();
		//}
		//u32 waitresult = WaitForSingleObject(This->_device_event,This->_pool_delay);
		//if(waitresult == WAIT_OBJECT_0)
		Sleep(This->_pool_delay);
		//{
			//ResetEvent(This->_device_event);
			This->update();			
		//}
	}
	//This->_InputDevice->SetEventNotification(NULL);
	This->_InputDevice->Unacquire();
	return 0;
}

//........................................................................................

void CInputDevice::start(u32 freq,u32 priority)
{
	_pool_delay = 1000/freq;
	if(!_is_device_thread_run)
	{		
		//_device_event = CreateEvent(NULL,TRUE,FALSE,NULL);		
//		if(_device_event)
//		{						
			_is_device_thread_run = true;
			_device_thread = CreateThread(NULL,0,_device_thread_proc,this,0,NULL);
			if(_device_thread)
			{
				SetThreadPriority(_device_thread,priority);
				return;
			}			
//		}
		_device_thread = INVALID_HANDLE_VALUE;
		//_device_event = INVALID_HANDLE_VALUE;
		_is_device_thread_run = false;
	}
}

//........................................................................................

void CInputDevice::stop(void)
{
	_is_device_thread_run = false;	
	//SetEvent(_device_event);
	if(_device_thread != INVALID_HANDLE_VALUE)
	{
		u32 waitresult = WaitForSingleObject(_device_thread,INFINITE);
		if(waitresult == WAIT_TIMEOUT)
		{
			TerminateThread(_device_thread,1);
		}				
		//	CloseHandle(_device_event);
		_device_thread = INVALID_HANDLE_VALUE;
		//_device_event = INVALID_HANDLE_VALUE;
	}

}