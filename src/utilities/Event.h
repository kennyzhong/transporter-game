#ifndef CEVENT_H
#define CEVENT_H
#include "base/datatypes.h"
#include <windows.h>

template <class FN> class BaseEvent
{
	protected : std::vector<std::pair<FN,void*>> handlers;
	public    : bit isactive;
				BaseEvent(void)
				{
					isactive = true; 
				}
				~BaseEvent(void)
				{ 
					isactive = false; 
				}				
				u32 count_handler(void) 
				{
					u32 result = 0;
					result = handlers.size(); 
					return result;
				}
				void clear_handler(void) 
				{
					handlers.clear();
				}
				void disconnect(FN func_handler)
				{
					for(u32 i=0 ; i<handlers.size() ; i++)
					{
						if(handlers.at(i).first == func_handler)
						{
							handlers.erase(handlers.begin()+i);
							return;
						}
					}
				}
				inline void connect(FN func_handler,void* func_owner=NULL)
				{
					handlers.push_back(std::make_pair(func_handler,func_owner));
				}
};

//————————————————————————————————————————————————————————————————————————————————————————

template<typename A> class Event : public BaseEvent<void (*)(void* owner,A args)>
{															
	public    : virtual void operator()(A params) 
				{ 
					trigger(params); 
				}			    
				virtual void trigger(A params)
				{
					if( isactive )
					{
						for( u32 i=0 ; i<handlers.size() ; i++ )
						{
							handlers.at(i).first(handlers.at(i).second,params);
						}
					}
				}
};

//————————————————————————————————————————————————————————————————————————————————————————

template<typename A1,typename A2> class Event2 
	: public BaseEvent<void (*)(void* owner,A1 p1,A2 p2)>
{															
public    : virtual void operator()(A1 p1,A2 p2) 
			{ 
				trigger(p1,p2); 
			}			    
			virtual void trigger(A1 p1,A2 p2)
			{
				if( isactive )
				{
					for( u32 i=0 ; i<handlers.size() ; i++ )
					{
						handlers.at(i).first(handlers.at(i).second,p1,p2);
					}
				}
			}
};

//————————————————————————————————————————————————————————————————————————————————————————

template<typename A1,typename A2, typename A3> class Event3 
: public BaseEvent<void (*)(void* owner,A1 p1,A2 p2,A3 p3)>
{															
public    : virtual void operator()(A1 p1,A2 p2,A3 p3) 
			{ 
				trigger(p1,p2,p3); 
			}			    
			virtual void trigger(A1 p1,A2 p2,A3 p3)
			{
				if( isactive )
				{
					for( u32 i=0 ; i<_fphandler_list.size() ; i++ )
					{
						handlers.at(i).first(handlers.at(i).second,p1,p2,p3);
					}
				}
			}
};

//————————————————————————————————————————————————————————————————————————————————————————

template<typename A1,typename A2, typename A3, typename A4> class Event4 
: public BaseEvent<void (*)(void* owner,A1 p1,A2 p2,A3 p3, A4 p4)>
{															
public    : virtual void operator()(A1 p1,A2 p2,A3 p3,A4 p4) 
			{ 
				trigger(p1,p2,p3,p4); 
			}			    
			virtual void trigger(A1 p1,A2 p2,A3 p3,A4 p4)
			{
				if( isactive )
				{
					for( u32 i=0 ; i<_fphandler_list.size() ; i++ )
					{
						handlers.at(i).first(handlers.at(i).second,p1,p2,p3,p4);
					}
				}
			}
};

//————————————————————————————————————————————————————————————————————————————————————————


#endif