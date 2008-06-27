#include "input/CInputEngine.h"

CInputManager::CInputManager(void)
:CBaseObject("InputManager")
{
	_DirectInput = NULL;
	_keyboard = new CInputKeyboard(this);
	_mouse = new CInputMouse(this);
	inputmap = &_maps;
	_active_map = NULL;
	_eventtrigger = new CInputEventTrigger(this);
}

//........................................................................................

CInputManager::~CInputManager(void)
{
	stop();
	if(_keyboard)
	{
		delete _keyboard;
		_keyboard = NULL;
	}

	if(_mouse)
	{
		delete _mouse;
		_mouse = NULL;
	}

	if(_DirectInput)
	{
		_DirectInput->Release();
		_DirectInput = NULL;
	}

	if(_eventtrigger)
	{
		delete _eventtrigger;
		_eventtrigger = NULL;
	}
}

//........................................................................................

CInputKeyboard* CInputManager::get_keyboard(void)
{
	return _keyboard;
}

//........................................................................................

CInputMouse* CInputManager::get_mouse(void)
{
	return _mouse;
}

//........................................................................................

bit CInputManager::init(HINSTANCE hInstance,HWND hWnd)
{
	if (FAILED (DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
									IID_IDirectInput8,
									(void**) &_DirectInput, NULL)))
	{
		return false;
	}
	_mouse->init(hInstance,hWnd,_DirectInput);
	_keyboard->init(hInstance,hWnd,_DirectInput);

	_input_state._keystate = _keyboard->get_state();
	_input_state._mousestate = _mouse->get_state();
	return true;
}

//........................................................................................

void CInputManager::set_active_input_map(CInputMap* map)
{
	CInputMap* lastmap = _active_map;
	_active_map = map;
	onMapChanged(lastmap,_active_map);
}

//........................................................................................

CInputMap* CInputManager::create_input_map(str name)
{
	if( !inputmap[name] )
	{
		CInputMap* newmap = new CInputMap(name,&_input_state,_eventtrigger);
		_maps.push_back(newmap);
		return newmap;
	}
	return NULL;
}

//........................................................................................

bit CInputManager::destroy_input_map(CInputMap* map)
{
	i32 index = inputmap.indexof(map);
	if(index>=0)
	{		
		if(map == _active_map)
		{
			set_active_input_map(NULL);
		}
		_maps.erase(_maps.begin()+index);
		delete map;
		return true;
	}
	return false;
}

//........................................................................................

void CInputManager::destroy_allmap(void)
{
	while(_maps.size())
	{
		if(_maps.at(0) == _active_map)
		{
			set_active_input_map(NULL);
		}
		delete _maps.at(0);
		_maps.erase(_maps.begin());
	}
}

void CInputManager::start(u32 freq,u32 priority)
{
	if(_mouse)
	{
		_mouse->start(freq,priority);
		Sleep(100);
	}
	if(_keyboard)
	{
		_keyboard->start(freq,priority);
	}
}

void CInputManager::stop(void)
{
	if(_mouse)
	{
		_mouse->stop();
	}
	if(_keyboard)
	{
		_keyboard->stop();
	}
}

CInputMap* CInputManager::get_active_input_map(void) 
{
	return _active_map; 
}