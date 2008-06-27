#include "input/CInputEngine.h"

CInputMap::CInputMap(str name,CInputState* state,CInputEventTrigger* eventtrigger)
:CBaseObject(name),_state(state)
{
	trigger = eventtrigger;
}

CInputMap::~CInputMap(void)
{

}


