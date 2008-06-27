#ifndef CINPUTEVENT_H
#define CINPUTEVENT_H
#include "input/CInputEngine.h"

class CInputEventMouseBtnDown : public CInputEventObject
{
friend class CInputEventTrigger;
protected   : u32 _btn_param;
			  CInputEventMouseBtnDown(CInputManager* parent)
				  :CInputEventObject("inputevent_mousebtndown",(CBaseObject*)parent)
			  { }
			  void signal(u32 btn);
			  void call(void);
};

class CInputEventMouseBtnUp : public CInputEventObject
{
friend class CInputEventTrigger;
protected   : u32 _btn_param;
			  CInputEventMouseBtnUp(CInputManager* parent)
				  :CInputEventObject("inputevent_mousebtnup",(CBaseObject*)parent)
			  { }
			  void signal(u32 btn);
			  void call(void);
};

class CInputEventMouseClick : public CInputEventObject
{
friend class CInputEventTrigger;
protected   : u32 _btn_param;
			  CInputEventMouseClick(CInputManager* parent)
				  :CInputEventObject("inputevent_mouseclick",(CBaseObject*)parent)
			  { }
			  void signal(u32 btn);
			  void call(void);
};

class CInputEventMouseDblClick : public CInputEventObject
{
friend class CInputEventTrigger;
protected   : u32 _btn_param;
			  CInputEventMouseDblClick(CInputManager* parent)
				  :CInputEventObject("inputevent_mousedblclick",(CBaseObject*)parent)
			  { }
			  void signal(u32 btn);
			  void call(void);
};

class CInputEventMouseScroll : public CInputEventObject
{
friend class CInputEventTrigger;
protected   : u32 _dz_param;
			  CInputEventMouseScroll(CInputManager* parent)
				  :CInputEventObject("inputevent_mousescroll",(CBaseObject*)parent)
			  { }
			  void signal(u32 dz);
			  void call(void);
};

class CInputEventMouseMove : public CInputEventObject
{
friend class CInputEventTrigger;
protected   : i32 _dx_param;
			  i32 _dy_param;
			  CInputEventMouseMove(CInputManager* parent)
				  :CInputEventObject("inputevent_mousemove",(CBaseObject*)parent)
			  { }
			  void signal(i32 dx,i32 dy);
			  void call(void);
};

class CInputEventKeyDown : public CInputEventObject
{
friend class CInputEventTrigger;
protected   : u32 _btn_param;
			  CInputEventKeyDown(CInputManager* parent)
				  :CInputEventObject("inputevent_keydown",(CBaseObject*)parent)
			  { }
			  void signal(u32 btn);
			  void call(void);
};

class CInputEventKeyUp : public CInputEventObject
{
friend class CInputEventTrigger;
protected   : u32 _btn_param;
			  CInputEventKeyUp(CInputManager* parent)
				  :CInputEventObject("inputevent_keyup",(CBaseObject*)parent)
			  { }
			  void signal(u32 btn);
			  void call(void);
};

class CInputEventKeyPress : public CInputEventObject
{
friend class CInputEventTrigger;
protected   : u32 _btn_param;
			  CInputEventKeyPress(CInputManager* parent)
				  :CInputEventObject("inputevent_keypress",(CBaseObject*)parent)
			  { }
			  void signal(u32 btn);
			  void call(void);
};

class CInputEventTrigger : public CBaseObject
{
friend class CInputManager;
private : CInputEventMouseBtnDown* _EvMouseBtnDown;
		  CInputEventMouseBtnUp* _EvMouseBtnUp;
		  CInputEventMouseClick* _EvMouseClick;
		  CInputEventMouseDblClick* _EvMouseDblClick;
		  CInputEventMouseScroll* _EvMouseScroll;
		  CInputEventMouseMove* _EvMouseMove;
		  CInputEventKeyDown* _EvKeyDown;
		  CInputEventKeyUp* _EvKeyUp;
		  CInputEventKeyPress* _EvKeyPress;
		  CInputEventTrigger(CInputManager* parent);
		  ~CInputEventTrigger(void);
public  : void MouseBtnDown(u32 btn){_EvMouseBtnDown->signal(btn);};
		  void MouseBtnUp(u32 btn){_EvMouseBtnUp->signal(btn);};
		  void MouseBtnClick(u32 btn){_EvMouseClick->signal(btn);};
		  void MouseBtnDblClick(u32 btn){_EvMouseDblClick->signal(btn);};
		  void MouseScroll(i32 delta){_EvMouseScroll->signal(delta);};
		  void MouseMove(i32 dx,i32 dy){_EvMouseMove->signal(dx,dy);};
		  void KeyDown(u32 key){_EvKeyDown->signal(key);};
		  void KeyUp(u32 key){_EvKeyUp->signal(key);};
		  void KeyPress(u32 key){_EvKeyPress->signal(key);};
};


#endif