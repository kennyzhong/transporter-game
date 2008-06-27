#include "transporter.h"

InputSystem::InputSystem()
{
	engine = NULL;
	inputManager = NULL;
	defaultInputMap = NULL;
	isInited = false;

	ZeroMemory(msButtonDown,sizeof(bit)*8);
	ZeroMemory(msDeltaMovement,sizeof(i32)*3);
	ZeroMemory(msScreenPos,sizeof(i32)*3);
}

//————————————————————————————————————————————————————————————————————————————————————————

InputSystem::~InputSystem()
{
	if(engine)
	{
		delete engine;
		engine = NULL;
		inputManager = NULL;
		defaultInputMap = NULL;
		isInited = false;
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

void InputSystem::init( Game* game )
{
	if(!isInited)
	{
		this->game = game;
		window = game->visual.getWindowHandle();
		engine = new CInputEngine(game->getAppInstance(),window);
		inputManager = engine->get_input_manager();

		defaultInputMap = inputManager->create_input_map("default");

		defaultInputMap->onMouseMove.connect(onMouseMove,this);
		defaultInputMap->onMouseScroll.connect(onMouseScroll,this);
		defaultInputMap->onMouseBtnDown.connect(onMouseBtnDown,this);
		defaultInputMap->onMouseBtnUp.connect(onMouseBtnUp,this);

		inputManager->set_active_input_map(defaultInputMap);

		isInited = true;
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

void InputSystem::run( u32 threadFreq,u32 threadPriority )
{
	if(isInited)
	{
		engine->start(threadFreq,threadPriority);
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

void InputSystem::stop()
{
	if(engine)
	{
		engine->stop();
		ZeroMemory(msButtonDown,sizeof(bit)*8);
		ZeroMemory(msDeltaMovement,sizeof(i32)*3);
		ZeroMemory(msScreenPos,sizeof(i32)*3);
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

void InputSystem::onMouseMove(void* userptr,i32 dx,i32 dy,CInputMap* map)
{
	InputSystem* This = (InputSystem*)userptr;

	RECT wrect;
	GetWindowRect(This->window,&wrect);
	i32 screenWidth  = wrect.right - wrect.left;
	i32 screenHeight = wrect.bottom - wrect.top;

	This->msDeltaMovement[0] = dx;
	This->msDeltaMovement[1] = dy;
	This->msScreenPos[0] += dx;
	This->msScreenPos[1] += dy;

	if(This->msScreenPos[0] > screenWidth)
	{
		This->msScreenPos[0] = screenWidth;
	}
	else if(This->msScreenPos[0] < 0)
	{
		This->msScreenPos[0] = 0;
	}

	if(This->msScreenPos[1] > screenHeight)
	{
		This->msScreenPos[1] = screenHeight;
	}
	else if(This->msScreenPos[1] < 0)
	{
		This->msScreenPos[1] = 0;
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

void InputSystem::onMouseScroll(void* userptr,i32 dz,CInputMap* map)
{
	InputSystem* This = (InputSystem*)userptr;

	This->msDeltaMovement[2] = dz;
	This->msScreenPos[2] += dz;

	if(This->msScreenPos[2] > 1000)
	{
		This->msScreenPos[2] = 1000;
	}
	else if(This->msScreenPos[2] < 0)
	{
		This->msScreenPos[2] = 0;
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

void InputSystem::onMouseBtnDown(void* userptr,u32 btn,CInputMap* map)
{
	InputSystem* This = (InputSystem*)userptr;
	This->msButtonDown[btn - DIMOFS_BUTTON0] = true;
}

//————————————————————————————————————————————————————————————————————————————————————————

void InputSystem::onMouseBtnUp(void* userptr,u32 btn,CInputMap* map)
{
	InputSystem* This = (InputSystem*)userptr;
	This->msButtonDown[btn - DIMOFS_BUTTON0] = false;
}

//————————————————————————————————————————————————————————————————————————————————————————

bit InputSystem::getMouseBtnState( u32 btn )
{
	if(btn >=0 && btn <8)
	{
		return msButtonDown[btn];
	}
	return false;
}

//————————————————————————————————————————————————————————————————————————————————————————

i32 InputSystem::getMouseMovement( u32 axis )
{
	if(axis >=0 && axis<3)
	{
		return msDeltaMovement[axis];
	}
	return 0;
}

//————————————————————————————————————————————————————————————————————————————————————————

i32 InputSystem::getMouseScreenPos( u32 axis )
{
	if(axis >=0 && axis<3)
	{
		return msScreenPos[axis];
	}
	return 0;
}

//————————————————————————————————————————————————————————————————————————————————————————

void InputSystem::resetMouseMovement( u32 axis )
{
	if(axis >=0 && axis<3)
	{
		msDeltaMovement[axis] = 0;
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

void InputSystem::resetMouseMovement()
{
	ZeroMemory(msDeltaMovement,sizeof(i32)*3);
}
//————————————————————————————————————————————————————————————————————————————————————————
