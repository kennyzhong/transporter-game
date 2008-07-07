#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "transporter.h"

class InputSystem : public InputEngine
{
protected : Game* game;
			HWND window;
			bit isInited;
			i32 msDeltaMovement[3];
			i32 msScreenPos[3];

			static void onMouseMove(void* userptr,i32 dx,i32 dy);
			static void onMouseScroll(void* userptr,i32 dz);
			static void onKeyPress(void* userptr,u32 btn);

public    : InputSystem();
			~InputSystem();

			bit init(Game* game,u32 threadFreq=60,u32 threadPriority = NORMAL_PRIORITY_CLASS);

			i32 getMouseMovement(u32 axis);
			i32 getMouseScreenPos(u32 axis);
			void resetMouseMovement(u32 axis);
			void resetMouseMovement();

};
#endif