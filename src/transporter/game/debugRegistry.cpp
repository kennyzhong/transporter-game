#include "transporter.h"

static DebugRegistry* volatile debugRegistry;

DebugRegistryBaseItem::DebugRegistryBaseItem( str name )
{
	debugItemName = name;
}

//————————————————————————————————————————————————————————————————————————————————————————

DebugRegistryBaseItem::~DebugRegistryBaseItem()
{
	DebugRegistry::getInstance()->removeItem(this->debugItemName);
}

//————————————————————————————————————————————————————————————————————————————————————————

str DebugRegistryBaseItem::getDebugItemName()
{
	return debugItemName;
}

//————————————————————————————————————————————————————————————————————————————————————————

DebugRegistry::DebugRegistry()
{
	InitializeCriticalSection(&lock);
}

//————————————————————————————————————————————————————————————————————————————————————————

DebugRegistry::~DebugRegistry()
{
	EnterCriticalSection(&lock);
	items.clear();
	LeaveCriticalSection(&lock);
	DeleteCriticalSection(&lock);
}

//————————————————————————————————————————————————————————————————————————————————————————

void DebugRegistry::destroyDebugRegistry()
{
	if(debugRegistry)
	{
		delete debugRegistry;
		debugRegistry = NULL;
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

DebugRegistry* DebugRegistry::getInstance()
{
	static DebugRegistry* volatile selfPtr;
	if( selfPtr == NULL)
	{
		DebugRegistry* newDebugRegistry = new DebugRegistry;
		LONG value = InterlockedCompareExchange((LONG*)&selfPtr,(LONG)newDebugRegistry,NULL);
		if( value != NULL )
		{
			delete newDebugRegistry;
		}
		else
		{
			debugRegistry = selfPtr;
			atexit(destroyDebugRegistry);
		}
	}	
	return selfPtr;
}

//————————————————————————————————————————————————————————————————————————————————————————

DebugRegistryBaseItem* DebugRegistry::getItem( str name )
{
	EnterCriticalSection(&lock);
	std::map<str,DebugRegistryBaseItem*>::iterator it = items.find(name);
	if(it != items.end())
	{
		DebugRegistryBaseItem* item = it->second;
		LeaveCriticalSection(&lock);
		return item;
	}
	LeaveCriticalSection(&lock);
	return NULL;
}

//————————————————————————————————————————————————————————————————————————————————————————

bit DebugRegistry::addItem( DebugRegistryBaseItem* item )
{
	EnterCriticalSection(&lock);
	std::map<str,DebugRegistryBaseItem*>::iterator it = items.find(item->getDebugItemName());
	if(it == items.end())
	{
		items[item->getDebugItemName()] = item;
		LeaveCriticalSection(&lock);
		return true;
	}
	LeaveCriticalSection(&lock);
	return false;
}

//————————————————————————————————————————————————————————————————————————————————————————

void DebugRegistry::removeItem( str name )
{
	EnterCriticalSection(&lock);
	items.erase(name);
	LeaveCriticalSection(&lock);
}

//————————————————————————————————————————————————————————————————————————————————————————

str DebugRegistry::print()
{
	EnterCriticalSection(&lock);
	str result;
	std::map<str,DebugRegistryBaseItem*>::iterator it = items.begin();
	for(it ; it!=items.end() ; it++)
	{
		DebugRegistryBaseItem* item = it->second;
		result += item->print()+"\n";
	}
	LeaveCriticalSection(&lock);
	return result;
}