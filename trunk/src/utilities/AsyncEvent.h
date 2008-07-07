#ifndef ASYNCEVENT_H
#define ASYNCEVENT_H
#include "utilities/Event.h"


template <class FN> class BaseAsyncEvent : public BaseEvent<FN>
{
protected : HANDLE eventSignal;
			HANDLE eventThread;
			bit isThreadRunning;
			virtual void callHandlers() = 0;
			static DWORD WINAPI invokerThread(LPVOID param)
			{
				BaseAsyncEvent<FN>* This = (BaseAsyncEvent<FN>*)param;
				while(This->isThreadRunning)
				{
					if( WaitForSingleObject(This->eventSignal,INFINITE) == WAIT_OBJECT_0 &&
						This->isThreadRunning )
					{
						This->callHandlers();
					}
				}
				return 0;
			}
public    : BaseAsyncEvent()
			{
				isThreadRunning = true;
				eventSignal = CreateEvent(NULL,FALSE,FALSE,NULL);
				eventThread = CreateThread(NULL,0,invokerThread,this,0,NULL);
			}
			~BaseAsyncEvent()
			{
				isThreadRunning = false;
				TerminateThread(eventThread,1);
				eventThread = NULL;
				CloseHandle(eventSignal);
				eventSignal = NULL;
			}
};

template<typename A> class AsyncEvent : public BaseAsyncEvent<void (*)(void* owner,A args)>
{		
protected : A volatile eventParam;
			void callHandlers()
			{
				if( isactive )
				{
					for( u32 i=0 ; i<handlers.size() ; i++ )
					{
						handlers.at(i).first(handlers.at(i).second,eventParam);
					}
				}
			}
public    : virtual void operator()(A params) 
			{ 
				trigger(params); 
			}			    
			virtual void trigger(A params)
			{
				eventParam = params;
				SetEvent(eventSignal);
			}
};

template<typename A1,typename A2> class AsyncEvent2 
: public BaseAsyncEvent<void (*)(void* owner,A1 p1,A2 p2)>
{					
protected : A1 volatile eventParam1;
			A2 volatile eventParam2;
			void callHandlers()
			{
				if( isactive )
				{
					for( u32 i=0 ; i<handlers.size() ; i++ )
					{
						handlers.at(i).first(handlers.at(i).second,eventParam1,eventParam2);
					}
				}
			}
public    : virtual void operator()(A1 p1,A2 p2) 
			{ 
				trigger(p1,p2); 
			}			    
			virtual void trigger(A1 p1,A2 p2)
			{
				eventParam1 = p1;
				eventParam2 = p2;
				SetEvent(eventSignal);
			}
};

template<typename A1,typename A2, typename A3> class AsyncEvent3
: public BaseAsyncEvent<void (*)(void* owner,A1 p1,A2 p2,A3 p3)>
{				
protected : A1 volatile eventParam1;
			A2 volatile eventParam2;
			A3 volatile eventParam3;
			void callHandlers()
			{
				if( isactive )
				{
					for( u32 i=0 ; i<handlers.size() ; i++ )
					{
						handlers.at(i).first(handlers.at(i).second,eventParam1,eventParam2,eventParam3);
					}
				}
			}
public    : virtual void operator()(A1 p1,A2 p2,A3 p3) 
			{ 
				trigger(p1,p2,p3); 
			}			    
			virtual void trigger(A1 p1,A2 p2,A3 p3)
			{
				eventParam1 = p1;
				eventParam2 = p2;
				eventParam3 = p3;
				SetEvent(eventSignal);
			}
};

template<typename A1,typename A2, typename A3, typename A4> class AsyncEvent4 
: public BaseAsyncEvent<void (*)(void* owner,A1 p1,A2 p2,A3 p3, A4 p4)>
{				
protected : A1 volatile eventParam1;
		    A2 volatile eventParam2;
		    A3 volatile eventParam3;
			A4 volatile eventParam4;
			void callHandlers()
			{
				if( isactive )
				{
					for( u32 i=0 ; i<handlers.size() ; i++ )
					{
						handlers.at(i).first(handlers.at(i).second,eventParam1,eventParam2,eventParam3,eventParam4);
					}
				}
			}
public    : virtual void operator()(A1 p1,A2 p2,A3 p3,A4 p4) 
			{ 
				trigger(p1,p2,p3,p4); 
			}			    
			virtual void trigger(A1 p1,A2 p2,A3 p3,A4 p4)
			{
				eventParam1 = p1;
				eventParam2 = p2;
				eventParam3 = p3;
				eventParam4 = p4;
				SetEvent(eventSignal);
			}
};
#endif