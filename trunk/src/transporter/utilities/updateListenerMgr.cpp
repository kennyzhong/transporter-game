#include "transporter.h"

static UpdateListenerMgr* volatile updateListenerMgr;

void UpdateListenerMgr::destroyUpdateListenerMgr()
{
	if(updateListenerMgr)
	{
		delete updateListenerMgr;
		updateListenerMgr = NULL;
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

UpdateListenerMgr::UpdateListenerMgr()
{
	InitializeCriticalSection(&lock);
}

//————————————————————————————————————————————————————————————————————————————————————————

UpdateListenerMgr::~UpdateListenerMgr()
{
	EnterCriticalSection(&lock);
	listeners.clear();
	LeaveCriticalSection(&lock);
	DeleteCriticalSection(&lock);
}

//————————————————————————————————————————————————————————————————————————————————————————

UpdateListenerMgr* UpdateListenerMgr::getInstance()
{
	static UpdateListenerMgr* volatile selfPtr;
	if( selfPtr == NULL)
	{
		UpdateListenerMgr* newUpdateListenerMgr = new UpdateListenerMgr;
		LONG value = InterlockedCompareExchange((LONG*)&selfPtr,(LONG)newUpdateListenerMgr,NULL);
		if( value != NULL )
		{
			delete newUpdateListenerMgr;
		}
		else
		{
			updateListenerMgr = selfPtr;
			atexit(destroyUpdateListenerMgr);
		}
	}	
	return selfPtr;
}

//————————————————————————————————————————————————————————————————————————————————————————

void UpdateListenerMgr::addListener( UpdateListener* listener )
{
	EnterCriticalSection(&lock);
	std::vector<UpdateListener*>::iterator it = listeners.begin();
	for(it ; it!=listeners.end() ; it++)
	{
		if(*it == listener)
		{
			LeaveCriticalSection(&lock);
			return;
		}
	}
	listeners.push_back(listener);
	LeaveCriticalSection(&lock);
}

//————————————————————————————————————————————————————————————————————————————————————————

void UpdateListenerMgr::removeListener( UpdateListener* listener )
{
	EnterCriticalSection(&lock);
	std::vector<UpdateListener*>::iterator it = listeners.begin();
	for(it ; it!=listeners.end() ; it++)
	{
		if(*it == listener)
		{
			listeners.erase(it);
			break;
		}
	}
	LeaveCriticalSection(&lock);
}

//————————————————————————————————————————————————————————————————————————————————————————

void UpdateListenerMgr::update( u32 evId,u32 param )
{
	EnterCriticalSection(&lock);
	std::vector<UpdateListener*>::iterator it = listeners.begin();
	for(it ; it!=listeners.end() ; it++)
	{
		UpdateListener* listener = *it;
		listener->update(evId,param);
	}
	LeaveCriticalSection(&lock);
}