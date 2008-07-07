#include "transporter.h"

static RTLog* volatile rtLog;

RTLog::RTLog()
{
	InitializeCriticalSection(&lock);
}

//————————————————————————————————————————————————————————————————————————————————————————

RTLog::~RTLog()
{
	EnterCriticalSection(&lock);
	logs.clear();
	LeaveCriticalSection(&lock);
	DeleteCriticalSection(&lock);
}

//————————————————————————————————————————————————————————————————————————————————————————

void RTLog::destroyRTLog()
{
	if(rtLog)
	{
		delete rtLog;
		rtLog = NULL;
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

RTLog* RTLog::getInstance()
{
	static RTLog* volatile selfPtr;
	if( selfPtr == NULL)
	{
		RTLog* newLogs = new RTLog;
		LONG value = InterlockedCompareExchange((LONG*)&selfPtr,(LONG)newLogs,NULL);
		if( value != NULL )
		{
			delete newLogs;
		}
		else
		{
			rtLog = selfPtr;
			atexit(destroyRTLog);
		}
	}	
	return selfPtr;
}

//————————————————————————————————————————————————————————————————————————————————————————

void RTLog::write( str logText )
{
	RTLog* This = RTLog::getInstance();
	EnterCriticalSection(&This->lock);
	std::vector<str> textItems = strexplodestr("\n",logText);
	for(u32 i=0 ; i<textItems.size() ; i++)
	{
		This->logs.push_back(textItems.at(i));
	}
	if(This->logs.size() > MAX_LOG_ENTRIES)
	{
		u32 toDelete = This->logs.size() - MAX_LOG_ENTRIES;
		for(u32 i=0 ; i<toDelete ; i++)
		{
			This->logs.erase(This->logs.begin());
		}
	}
	LeaveCriticalSection(&This->lock);
}

//————————————————————————————————————————————————————————————————————————————————————————

str RTLog::getLog( u32 index )
{
	str result = "";
	RTLog* This = RTLog::getInstance();
	EnterCriticalSection(&This->lock);
	if(index < This->logs.size())
	{
		result = This->logs.at(This->logs.size() - index - 1);
	}
	LeaveCriticalSection(&This->lock);	
	return result;
}

//————————————————————————————————————————————————————————————————————————————————————————

u32 RTLog::count()
{
	u32 result = 0;
	RTLog* This = RTLog::getInstance();
	EnterCriticalSection(&This->lock);
	result = This->logs.size();
	LeaveCriticalSection(&This->lock);	
	return result;
}