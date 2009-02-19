#include "transporter.h"

InputSystem::InputSystem()
{
	isInited = false;
	ZeroMemory(msDeltaMovement,sizeof(i32)*3);
	ZeroMemory(msScreenPos,sizeof(i32)*3);
}

//————————————————————————————————————————————————————————————————————————————————————————

InputSystem::~InputSystem()
{
	isInited = false;
	mouse.onMouseMove.disconnect(onMouseMove);
	mouse.onMouseScroll.disconnect(onMouseScroll);
	keyboard.onKeyPress.disconnect(onKeyPress);
}

//————————————————————————————————————————————————————————————————————————————————————————

bit InputSystem::init( Game* game,u32 threadFreq,u32 threadPriority)
{
	if(!this->isInited)
	{
		this->game = game;
		window = game->visualSystem.getWindowHandle(game->visualSystem.getPrimaryRenderWindow());
		isInited = InputEngine::init(game->getAppInstance(),window,threadFreq,threadPriority);

		mouse.onMouseMove.connect(onMouseMove,this);
		mouse.onMouseScroll.connect(onMouseScroll,this);
		keyboard.onKeyPress.connect(onKeyPress,this);
	}
	return true;
}

//————————————————————————————————————————————————————————————————————————————————————————

void InputSystem::onMouseMove(void* userptr,i32 dx,i32 dy)
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

void InputSystem::onMouseScroll(void* userptr,i32 dz)
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

void InputSystem::onKeyPress( void* userptr,u32 btn )
{
	InputSystem* self = (InputSystem*)userptr;
	if(btn == DIK_F1)
	{
		self->game->bootScene.showLog(!self->game->bootScene.isLogVisible());
	}
	else if(btn == DIK_F2)
	{
		static bit isWireframe;
		isWireframe = !isWireframe;
		if(isWireframe)
		{
			self->game->visualSystem.getCamera()->setPolygonMode(Ogre::PM_WIREFRAME);
		}
		else
		{
			self->game->visualSystem.getCamera()->setPolygonMode(Ogre::PM_SOLID);
		}
	}
}
//————————————————————————————————————————————————————————————————————————————————————————
