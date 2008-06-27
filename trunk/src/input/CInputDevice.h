#ifndef CINPUTDEVICE_H
#define CINPUTDEVICE_H

#include "input/CInputEngine.h"

class MTINPUT_API CInputDevice : public CBaseObject
{
protected : IDirectInputDevice8* _InputDevice;
			CInputMap* _active_map;
			//HANDLE _device_event;
			HANDLE _device_thread;
			bit _is_device_thread_run;
			u32 _pool_delay;
			static DWORD WINAPI _device_thread_proc(LPVOID param);
			virtual void changemap(CInputMap* newmap);
			static void evMapChanged(void* owner,CInputMap* oldmap,CInputMap* newmap);
public    : CInputDevice(str objectname,CInputManager* parent);
		    virtual ~CInputDevice(void);			
			virtual void update(void)=0;

			virtual void start(u32 freq,u32 priority);
			virtual void stop(void);
			
};
#endif