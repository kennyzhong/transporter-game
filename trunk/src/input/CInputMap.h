#ifndef CINPUTMAP_H
#define CINPUTMAP_H

#include "input/CInputEngine.h"

class MTINPUT_API CInputMap : public CBaseObject
{
	friend class CInputManager;
	protected : CInputMap(str name,CInputState* state,CInputEventTrigger* eventtrigger);
				~CInputMap(void);
				CInputState* _state;
	public    : Event2<u32,CInputMap*> onMouseBtnDown;
				Event2<u32,CInputMap*> onMouseBtnUp;
				Event2<u32,CInputMap*> onMouseBtnClick;
				Event2<u32,CInputMap*> onMouseBtnDblClick;
				Event2<i32,CInputMap*> onMouseScroll;
				Event3<i32,i32,CInputMap*> onMouseMove;
				Event2<u32,CInputMap*> onKeyDown;
				Event2<u32,CInputMap*> onKeyUp;
				Event2<u32,CInputMap*> onKeyPress;
				//CEvent4<u32,u32,u32,CInputMap*> onJoyMove;
				//CEvent2<u32,CInputMap*> onJoyBtnDown;
				//CEvent2<u32,CInputMap*> onJoyBtnUp;
				//CEvent2<u32,CInputMap*> onJoyBtnPress;

				CInputState* get_state(void){return _state;}
				CInputEventTrigger* trigger;
};

#endif