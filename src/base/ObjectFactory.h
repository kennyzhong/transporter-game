#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H
#include "base/datatypes.h"
#include "base/object.h"
#include <windows.h>
#include <vector>
#include <map>

class BaseObjectFactory;

class ObjectFactoryMgr
{
friend class BaseObjectFactory;
private   : 
protected : std::vector<BaseObjectFactory*> factoryList;
			std::map<u32,BaseObjectFactory*> factoryMap;
			std::map<BaseObjectFactory*,u32> factoryInvMap;
			CRITICAL_SECTION lock;
			u32 currentClassId;

			ObjectFactoryMgr();
			~ObjectFactoryMgr();
			void clear();
			static u32 registerFactory(BaseObjectFactory* factory);
			static void unregisterFactory(BaseObjectFactory* factory);
			static ObjectFactoryMgr* getInstance();
			static void destroyFactoryMgr();
public    : static BaseObjectFactory* getFactory(u32 classId);
};

//----------------------------------------------------------------------------------------

class BaseObjectFactory
{
friend class ObjectFactoryMgr;
protected : u32 classId;
			u32 currentObjectId;
			BaseObjectFactory();
			virtual ~BaseObjectFactory();
public	  : u32 getClassId();
			u32 getLastObjectId();

			virtual Object* create() = 0;
			virtual bit destroy(IN Object* object) = 0;
			virtual bit destroy(IN u32 objectId) = 0;
			virtual u32 clear() = 0;
			virtual u32 indexOf(IN Object* object) = 0;
			virtual Object* get(u32 objectId) = 0;
			virtual Object* at(u32 ndx) = 0;
			virtual u32 count() = 0;
};

//----------------------------------------------------------------------------------------

template <typename T> class ObjectFactory : public BaseObjectFactory
{
protected : std::vector<T*> objectList;
			std::map<u32,T*> objectMap;
			std::map<T*,u32> objectInvMap;
			CRITICAL_SECTION lock;
			virtual T* construct(u32 classId,u32 objectId);
			ObjectFactory();
			virtual ~ObjectFactory();
public    : virtual Object* create();
			virtual bit destroy(IN Object* object);
			virtual bit destroy(IN u32 objectId);
			virtual u32 clear();
			virtual u32 indexOf(IN Object* object);
			virtual Object* get(u32 objectId);
			virtual Object* at(u32 ndx);
			virtual u32 count();
			static ObjectFactory<T>* getInstance();
};

//----------------------------------------------------------------------------------------

template <typename T>
T* ObjectFactory<T>::construct( u32 classId,u32 objectId)
{
	return new T(classId,objectId );
}

//........................................................................................

template <typename T> Object* ObjectFactory<T>::create()
{
	T* newObject = NULL;
	EnterCriticalSection(&lock);
	try
	{
		this->currentObjectId++;
		newObject = construct(this->classId,this->currentObjectId);
		objectList.push_back(newObject);
		objectMap[this->currentObjectId] = newObject;
		objectInvMap[newObject] = this->currentObjectId;
		LeaveCriticalSection(&lock);
	}
	catch (...)
	{
		LeaveCriticalSection(&lock);
		return NULL;
	}				
	return newObject;
}

//........................................................................................

template <typename T> bit ObjectFactory<T>::destroy( IN Object* object )
{
	EnterCriticalSection(&lock);
	try
	{
		std::vector<T*>::iterator vec_it = objectList.begin();
		for(vec_it ; vec_it != objectList.end() ; vec_it++)
		{
			if( *vec_it == object )
			{
				objectList.erase(vec_it);
				std::map<T*,u32>::iterator map_it = objectInvMap.find((T*)object);
				if(map_it != objectInvMap.end())
				{
					objectMap.erase(map_it->second);
				}
				objectInvMap.erase((T*)object);
				delete object;
				LeaveCriticalSection(&lock);
				return true;
			}
		}
	}
	catch (...)
	{
		LeaveCriticalSection(&lock);
		return false;
	}

	LeaveCriticalSection(&lock);
	return false;
}

//........................................................................................

template <typename T> u32 ObjectFactory<T>::clear()
{
	u32 curSize = objectList.size();
	while(objectList.size())
	{
		destroy(at(0));
	}
	return curSize;
}

//........................................................................................

template <typename T> u32 ObjectFactory<T>::indexOf( IN Object* object )
{
	EnterCriticalSection(&lock);
	try
	{
		for(u32 i=0 ; i<count() ; i++)
		{
			if(objectList.at(i) == object)
			{
				LeaveCriticalSection(&lock);
				return i;
			}
		}
	}
	catch (...)
	{
		LeaveCriticalSection(&lock);
		return (u32)-1;
	}
	LeaveCriticalSection(&lock);
	return (u32)-1;
}

//........................................................................................

template <typename T> Object* ObjectFactory<T>::get( u32 objectId )
{
	EnterCriticalSection(&lock);
	try
	{
		std::map<u32,T*>::iterator it = objectMap.find(objectId);
		if(it != objectMap.end())
		{
			T* result = it->second;
			LeaveCriticalSection(&lock);
			return result;
		}
	}
	catch (...)
	{
		LeaveCriticalSection(&lock);
		return NULL;
	}
	LeaveCriticalSection(&lock);
	return NULL;
}

//........................................................................................

template <typename T> Object* ObjectFactory<T>::at( u32 ndx )
{
	T* result = NULL;
	EnterCriticalSection(&lock);
	try
	{
		if(ndx < objectList.size())
		{
			result = objectList.at(ndx);
		}
	}
	catch (...)
	{
		LeaveCriticalSection(&lock);
		return NULL;
	}
	LeaveCriticalSection(&lock);
	return result;
}

//........................................................................................

template <typename T> u32 ObjectFactory<T>::count()
{
	u32 result = 0;
	EnterCriticalSection(&lock);
	try
	{
		result = objectList.size();
	}
	catch (...)
	{
		LeaveCriticalSection(&lock);
		return 0;
	}
	LeaveCriticalSection(&lock);
	return result;
}

//........................................................................................

template <typename T> ObjectFactory<T>* ObjectFactory<T>::getInstance()
{
	static ObjectFactory<T>* volatile selfPtr;
	if( selfPtr == NULL)
	{
		ObjectFactory<T>* newFactory = new ObjectFactory<T>;
		LONG value = InterlockedCompareExchange((LONG*)&selfPtr,(LONG)newFactory,NULL);
		if( value != NULL )
		{
			delete newFactory;
		}
	}	
	return selfPtr;
}

//........................................................................................

template <typename T> bit ObjectFactory<T>::destroy( IN u32 objectId )
{
	return destroy(get(objectId));
}

//........................................................................................

template <typename T> ObjectFactory<T>::ObjectFactory()
{
	InitializeCriticalSection(&lock);
}

//........................................................................................

template <typename T> ObjectFactory<T>::~ObjectFactory()
{
	clear(); 
	DeleteCriticalSection(&lock);
}

//........................................................................................
#endif