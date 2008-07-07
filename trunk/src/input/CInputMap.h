#ifndef CINPUTMAP_H
#define CINPUTMAP_H

#include "input/CInputEngine.h"

class MTINPUT_API InputMap
{
public : Event2<u32> onMouseBtnDown;
		 Event2<u32> onMouseBtnUp;
		 Event2<u32> onMouseBtnClick;
		 Event2<u32> onMouseBtnDblClick;
		 Event2<i32> onMouseScroll;
		 Event3<i32,i32> onMouseMove;
		 Event2<u32> onKeyDown;
		 Event2<u32> onKeyUp;
		 Event2<u32> onKeyPress;
};

class MTINPUT_API InputMaps;
{
protected : std::vector<InputMap*> inputMaps;
			CRITICAL_SECTION lockHandle;			
public    : void addInputMap(InputMap* inputMap);
			void removeInputMap(InputMap* inputMap);
			InputMap* getInputMap(u32 index);
			u32 countInputMap();
			InputMap primaryMap;
};

#endif