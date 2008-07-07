#ifndef CINPUTDEVICE_H
#define CINPUTDEVICE_H

#include "input/InputEngine.h"

class MTINPUT_API InputDevice
{
protected : IDirectInputDevice8* deviceHandle;
			IDirectInput8* directInputInterface;
			InputEngine* engine;
			HANDLE deviceThread;
			HANDLE deviceThreadSignal;
			HANDLE deviceInitSignal;
			HINSTANCE appInstance;
			HWND windowHandle;
			bit isThreadRunning;
			bit isDeviceInited;
			u32 threadFrequency;
			u32 threadPriority;
			bit reInit();
			str name;
			virtual bit initDevice(HINSTANCE hInstance,HWND hWnd,
				             IN IDirectInput8* directInput,OUT IDirectInputDevice8** device) = 0;
			virtual void destroyDevice() = 0;
			virtual bit init( InputEngine* engine, HINSTANCE hInstance, HWND hWnd,
				              IDirectInput8* directInput, u32 freq = 60, 
							  u32 priority = THREAD_PRIORITY_NORMAL);
			static DWORD WINAPI deviceThreadProc(LPVOID params);
public    : InputDevice(str name);
			virtual ~InputDevice();			
			virtual void update()=0;
			virtual void start();
			virtual void stop();
};
#endif