#ifndef CINPUTMANAGER_H
#define CINPUTMANAGER_H
#include "input/CInputEngine.h"
#define INPUT_SIGNAL_COUNT 9

class CInputState
{
friend class CInputManager;
private : CInputKeyboardState* _keystate;
		  CInputMouseState* _mousestate;
		  CInputState(){};
public  : CInputKeyboardState* get_key_state(void){ return _keystate; };
		  CInputMouseState* get_mouse_state(void){ return _mousestate; };
};

class MTINPUT_API CInputManager : public CBaseObject
{
	friend class CInputEngine;
	protected : CInputManager(void);
				~CInputManager(void);
				IDirectInput8* _DirectInput;
				CInputKeyboard* _keyboard;
				CInputMouse* _mouse;
				CInputMap* _active_map;		
				CInputState _input_state;
				CInputEventTrigger* _eventtrigger;
				std::vector<CInputMap*> _maps;
				HANDLE _eventthread[9];
				HANDLE _eventsignal[9];
				void destroy_allmap(void);
				bit init(HINSTANCE hInstance,HWND hWnd);
	public    : CInputKeyboard* get_keyboard(void);
				CInputMouse* get_mouse(void);

				void start(u32 freq,u32 priority);
				void stop(void);				

				CInputMap* get_active_input_map(void);
				void set_active_input_map(CInputMap* map);
				CInputMap* create_input_map(str name);
				bit destroy_input_map(CInputMap* map);

				Event2<CInputMap*,CInputMap*> onMapChanged;
				CObjectVector<CInputMap*> inputmap;
};

#endif