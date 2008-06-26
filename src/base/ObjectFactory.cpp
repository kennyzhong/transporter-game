#include "base/ObjectFactory.h"

static ObjectFactoryMgr* volatile factoryMgrPtr;

ObjectFactoryMgr::ObjectFactoryMgr()
{
	InitializeCriticalSection(&lock);
	currentClassId = 0;
}

//........................................................................................

ObjectFactoryMgr::~ObjectFactoryMgr()
{
	clear();
	DeleteCriticalSection(&lock);
}

//........................................................................................

void ObjectFactoryMgr::clear()
{
	EnterCriticalSection(&lock);
	try
	{
		while(factoryList.size())
		{
			delete factoryList.at(0);
		}
	}
	catch (...)
	{
		LeaveCriticalSection(&lock);
		return;
	}
	LeaveCriticalSection(&lock);
}

//........................................................................................

u32 ObjectFactoryMgr::registerFactory( BaseObjectFactory* factory )
{
	u32 result = 0;
	ObjectFactoryMgr* self = ObjectFactoryMgr::getInstance();
	EnterCriticalSection(&self->lock);
	try
	{
		std::map<BaseObjectFactory*,u32>::iterator it = self->factoryInvMap.find(factory);
		if(it != self->factoryInvMap.end())
		{
			result = it->second;
		}
		else
		{						
			result = ++self->currentClassId;
			self->factoryList.push_back(factory);
			self->factoryMap[self->currentClassId] = factory;
			self->factoryInvMap[factory] = self->currentClassId;
		}
	}
	catch (...)
	{
		LeaveCriticalSection(&self->lock);
		return 0;
	}				
	LeaveCriticalSection(&self->lock);
	return result;
}

//........................................................................................

void ObjectFactoryMgr::unregisterFactory( BaseObjectFactory* factory )
{
	ObjectFactoryMgr* self = ObjectFactoryMgr::getInstance();
	EnterCriticalSection(&self->lock);
	try
	{
		std::map<BaseObjectFactory*,u32>::iterator it = self->factoryInvMap.find(factory);
		if(it != self->factoryInvMap.end())
		{
			self->factoryMap.erase(it->second);
			self->factoryInvMap.erase(factory);
			std::vector<BaseObjectFactory*>::iterator vec_it = self->factoryList.begin();
			for(vec_it ; vec_it!=self->factoryList.end() ; vec_it++)
			{
				if(*vec_it == factory)
				{
					self->factoryList.erase(vec_it);
					break;
				}
			}
		}
	}
	catch (...)
	{
		LeaveCriticalSection(&self->lock);
		return;
	}				
	LeaveCriticalSection(&self->lock);
}

//........................................................................................

ObjectFactoryMgr* ObjectFactoryMgr::getInstance()
{
	static ObjectFactoryMgr* volatile selfPtr;
	if( selfPtr == NULL)
	{
		ObjectFactoryMgr* newFactoryMgr = new ObjectFactoryMgr;
		LONG value = InterlockedCompareExchange((LONG*)&selfPtr,(LONG)newFactoryMgr,NULL);
		if( value != NULL )
		{
			delete newFactoryMgr;
		}
		else
		{
			factoryMgrPtr = selfPtr;
			atexit(destroyFactoryMgr);
		}
	}	
	return selfPtr;
}

//........................................................................................

void ObjectFactoryMgr::destroyFactoryMgr()
{
	if(factoryMgrPtr)
	{
		delete factoryMgrPtr;
		factoryMgrPtr = NULL;
	}
}

//........................................................................................

BaseObjectFactory* ObjectFactoryMgr::getFactory( u32 classId )
{
	ObjectFactoryMgr* This = ObjectFactoryMgr::getInstance();
	std::map<u32,BaseObjectFactory*>::iterator it = This->factoryMap.find(classId);
	if(it!=This->factoryMap.end())
	{
		return it->second;
	}
	return NULL;
}

//----------------------------------------------------------------------------------------

BaseObjectFactory::BaseObjectFactory()
{
	classId = ObjectFactoryMgr::registerFactory(this);
	currentObjectId = 0;
}

BaseObjectFactory::~BaseObjectFactory()
{
	ObjectFactoryMgr::unregisterFactory(this);
}

u32 BaseObjectFactory::getClassId()
{
	return classId;
}
u32 BaseObjectFactory::getLastObjectId()
{
	return currentObjectId;
}