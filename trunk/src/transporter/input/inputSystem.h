#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "transporter.h"

class InputSystem
{
protected : CInputEngine* engine;
			CInputManager* inputManager;
			CInputMap* defaultInputMap;
			Game* game;
			HWND window;
			bit isInited;
			bit msButtonDown[8];
			i32 msDeltaMovement[3];
			i32 msScreenPos[3];

			static void onMouseMove(void* userptr,i32 dx,i32 dy,CInputMap* map);
			static void onMouseScroll(void* userptr,i32 dz,CInputMap* map);
			static void onMouseBtnDown(void* userptr,u32 btn,CInputMap* map);
			static void onMouseBtnUp(void* userptr,u32 btn,CInputMap* map);

public    : InputSystem();
			~InputSystem();

			bit init(Game* game);
			void run(u32 threadFreq=30,u32 threadPriority = NORMAL_PRIORITY_CLASS);
			void stop();	

			bit getMouseBtnState(u32 btn);
			i32 getMouseMovement(u32 axis);
			i32 getMouseScreenPos(u32 axis);
			void resetMouseMovement(u32 axis);
			void resetMouseMovement();
};
#endif