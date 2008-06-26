#ifndef CEVENT_H
#define CEVENT_H
#include "base/datatypes.h"
#include <windows.h>

template <class FN> class BaseEvent
{
	protected : std::vector<void*> _fpowner_list;
				std::vector<HANDLE> _signals;
				std::vector<FN> _fphandler_list;	
	public    : BaseEvent(void){ isactive = true; }
				~BaseEvent(void){ isactive = false; }
				bit isactive;
				u32 count_handler(void) { return _fphandler_list.size(); }
				void connect(HANDLE signal){ _signals.push_back(signal); }
				void clear_handler(void) 
				{
					_fphandler_list.clear();
					_fpowner_list.clear();
				}
				void disconnect(HANDLE signal)
				{
					for(u32 i=0 ; i<_signals.size() ; i++)
					{
						if(_signals.at(i) == signal)
						{
							_signals.erase(_signals.begin()+i);
							return;
						}
					}
				}
				void disconnect(FN func_handler)
				{
					for(u32 i=0 ; i<_fphandler_list.size() ; i++)
					{
						if(_fphandler_list.at(i) == func_handler)
						{
							_fpowner_list.erase(_fpowner_list.begin()+i);
							_fphandler_list.erase(_fphandler_list.begin()+i);
							return;
						}
					}
				}
				inline void connect(FN func_handler,void* func_owner=NULL)
				{
					_fpowner_list.push_back(func_owner);
					_fphandler_list.push_back(func_handler);
				}
};

//————————————————————————————————————————————————————————————————————————————————————————

template<typename A> class Event : public BaseEvent<void (*)(void* owner,A args)>
{															
	public    : void operator()(A params) 
				{ 
					trigger(params); 
				}			    
				void trigger(A params)
				{
					if( isactive )
					{
						for( u32 i=0 ; i<_signals.size() ; i++ )
						{
							SetEvent(_signals.at(i));
						}
						for( u32 i=0 ; i<_fphandler_list.size() ; i++ )
						{
							_fphandler_list.at(i)(_fpowner_list.at(i),params);
						}
					}
				}
};

//————————————————————————————————————————————————————————————————————————————————————————

template<typename A1,typename A2> class Event2 
	: public BaseEvent<void (*)(void* owner,A1 p1,A2 p2)>
{															
public    : void operator()(A1 p1,A2 p2) 
			{ 
				trigger(p1,p2); 
			}			    
			void trigger(A1 p1,A2 p2)
			{
				if( isactive )
				{
					for( u32 i=0 ; i<_signals.size() ; i++ )
					{
						SetEvent(_signals.at(i));
					}
					for( u32 i=0 ; i<_fphandler_list.size() ; i++ )
					{
						_fphandler_list.at(i)(_fpowner_list.at(i),p1,p2);
					}
				}
			}
};

//————————————————————————————————————————————————————————————————————————————————————————

template<typename A1,typename A2, typename A3> class Event3 
: public BaseEvent<void (*)(void* owner,A1 p1,A2 p2,A3 p3)>
{															
public    : void operator()(A1 p1,A2 p2,A3 p3) 
			{ 
				trigger(p1,p2,p3); 
			}			    
			void trigger(A1 p1,A2 p2,A3 p3)
			{
				if( isactive )
				{
					for( u32 i=0 ; i<_signals.size() ; i++ )
					{
						SetEvent(_signals.at(i));
					}
					for( u32 i=0 ; i<_fphandler_list.size() ; i++ )
					{
						_fphandler_list.at(i)(_fpowner_list.at(i),p1,p2,p3);
					}
				}
			}
};

//————————————————————————————————————————————————————————————————————————————————————————

template<typename A1,typename A2, typename A3, typename A4> class Event4 
: public BaseEvent<void (*)(void* owner,A1 p1,A2 p2,A3 p3, A4 p4)>
{															
public    : void operator()(A1 p1,A2 p2,A3 p3,A4 p4) 
			{ 
				trigger(p1,p2,p3,p4); 
			}			    
			void trigger(A1 p1,A2 p2,A3 p3,A4 p4)
			{
				if( isactive )
				{
					for( u32 i=0 ; i<_signals.size() ; i++ )
					{
						SetEvent(_signals.at(i));
					}
					for( u32 i=0 ; i<_fphandler_list.size() ; i++ )
					{
						_fphandler_list.at(i)(_fpowner_list.at(i),p1,p2,p3,p4);
					}
				}
			}
};

//————————————————————————————————————————————————————————————————————————————————————————


#endif