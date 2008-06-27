#include "input/CInputEngine.h"

void CInputEventMouseBtnDown::call(void)
{
	CInputManager* IM = (CInputManager*)_owner;
	CInputMap* map = IM->get_active_input_map();
	if(map)
	{
		map->onMouseBtnDown(_btn_param,map);
	}				
}		
void CInputEventMouseBtnDown::signal(u32 btn) 
{ 
	_btn_param = btn;
	if(_eventsignal != INVALID_HANDLE_VALUE)
	{
		SetEvent(_eventsignal); 
	}				
}

void CInputEventMouseBtnUp::call(void)
{
	CInputManager* IM = (CInputManager*)_owner;
	CInputMap* map = IM->get_active_input_map();
	if(map)
	{
		map->onMouseBtnUp(_btn_param,map);
	}				
}		
void CInputEventMouseBtnUp::signal(u32 btn) 
{ 
	_btn_param = btn;
	if(_eventsignal != INVALID_HANDLE_VALUE)
	{
		SetEvent(_eventsignal); 
	}				
}

void CInputEventMouseClick::call(void)
{
	CInputManager* IM = (CInputManager*)_owner;
	CInputMap* map = IM->get_active_input_map();
	if(map)
	{
		map->onMouseBtnClick(_btn_param,map);
	}				
}		
void CInputEventMouseClick::signal(u32 btn) 
{ 
	_btn_param = btn;
	if(_eventsignal != INVALID_HANDLE_VALUE)
	{
		SetEvent(_eventsignal); 
	}				
}

void CInputEventMouseDblClick::call(void)
{
	CInputManager* IM = (CInputManager*)_owner;
	CInputMap* map = IM->get_active_input_map();
	if(map)
	{
		map->onMouseBtnDblClick(_btn_param,map);
	}				
}		
void CInputEventMouseDblClick::signal(u32 btn) 
{ 
	_btn_param = btn;
	if(_eventsignal != INVALID_HANDLE_VALUE)
	{
		SetEvent(_eventsignal); 
	}				
}

void CInputEventMouseScroll::call(void)
{
	CInputManager* IM = (CInputManager*)_owner;
	CInputMap* map = IM->get_active_input_map();
	if(map)
	{
		map->onMouseScroll(_dz_param,map);
	}				
}		
void CInputEventMouseScroll::signal(u32 dz) 
{ 
	_dz_param = dz;
	if(_eventsignal != INVALID_HANDLE_VALUE)
	{
		SetEvent(_eventsignal); 
	}				
}

void CInputEventMouseMove::call(void)
{
	CInputManager* IM = (CInputManager*)_owner;
	CInputMap* map = IM->get_active_input_map();
	if(map)
	{
		map->onMouseMove(_dx_param,_dy_param,map);
	}				
}		
void CInputEventMouseMove::signal(i32 dx,i32 dy) 
{ 
	_dx_param = dx;
	_dy_param = dy;
	if(_eventsignal != INVALID_HANDLE_VALUE)
	{
		SetEvent(_eventsignal); 
	}				
}

void CInputEventKeyDown::call(void)
{
	CInputManager* IM = (CInputManager*)_owner;
	CInputMap* map = IM->get_active_input_map();
	if(map)
	{
		map->onKeyDown(_btn_param,map);
	}				
}		
void CInputEventKeyDown::signal(u32 btn) 
{ 
	_btn_param = btn;
	if(_eventsignal != INVALID_HANDLE_VALUE)
	{
		SetEvent(_eventsignal); 
	}				
}

void CInputEventKeyUp::call(void)
{
	CInputManager* IM = (CInputManager*)_owner;
	CInputMap* map = IM->get_active_input_map();
	if(map)
	{
		map->onKeyUp(_btn_param,map);
	}				
}		
void CInputEventKeyUp::signal(u32 btn) 
{ 
	_btn_param = btn;
	if(_eventsignal != INVALID_HANDLE_VALUE)
	{
		SetEvent(_eventsignal); 
	}				
}

void CInputEventKeyPress::call(void)
{
	CInputManager* IM = (CInputManager*)_owner;
	CInputMap* map = IM->get_active_input_map();
	if(map)
	{
		map->onKeyPress(_btn_param,map);
	}				
}		
void CInputEventKeyPress::signal(u32 btn) 
{ 
	_btn_param = btn;
	if(_eventsignal != INVALID_HANDLE_VALUE)
	{
		SetEvent(_eventsignal); 
	}				
}

CInputEventTrigger::CInputEventTrigger(CInputManager* parent)
:CBaseObject("input_event_trigger",(CBaseObject*)parent)
{
	_EvMouseBtnDown = new CInputEventMouseBtnDown(parent);
	_EvMouseBtnUp = new CInputEventMouseBtnUp(parent);
	_EvMouseClick = new CInputEventMouseClick(parent);
	_EvMouseDblClick = new CInputEventMouseDblClick(parent);
	_EvMouseScroll = new CInputEventMouseScroll(parent);
	_EvMouseMove = new CInputEventMouseMove(parent);
	_EvKeyDown = new CInputEventKeyDown(parent);
	_EvKeyUp = new CInputEventKeyUp(parent);
	_EvKeyPress = new CInputEventKeyPress(parent);
}

CInputEventTrigger::~CInputEventTrigger(void)
{
	if(_EvMouseBtnDown)
	{
		delete _EvMouseBtnDown;
		_EvMouseBtnDown = NULL;
	}
	if(_EvMouseBtnUp)
	{
		delete _EvMouseBtnUp;
		_EvMouseBtnUp = NULL;
	}
	if(_EvMouseClick)
	{
		delete _EvMouseClick;
		_EvMouseClick = NULL;
	}
	if(_EvMouseDblClick)
	{
		delete _EvMouseDblClick;
		_EvMouseDblClick = NULL;
	}
	if(_EvMouseScroll)
	{
		delete _EvMouseScroll;
		_EvMouseScroll = NULL;
	}
	if(_EvMouseMove)
	{
		delete _EvMouseMove;
		_EvMouseMove = NULL;
	}
	if(_EvKeyDown)
	{
		delete _EvKeyDown;
		_EvKeyDown = NULL;
	}
	if(_EvKeyUp)
	{
		delete _EvKeyUp;
		_EvKeyUp = NULL;
	}
	if(_EvKeyPress)
	{
		delete _EvKeyPress;
		_EvKeyPress = NULL;
	}
}