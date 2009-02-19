#include "transporter.h"

PhysicsSystem::PhysicsSystem()
{
	isPhysicsRunning = false;
	isPhysicsInited = false;
	physicsThread = NULL;
	physicsThreadSignal = NULL;
	scene = NULL;
	game = NULL;	
}

//————————————————————————————————————————————————————————————————————————————————————————

PhysicsSystem::~PhysicsSystem()
{
	cleanUp();
}

//————————————————————————————————————————————————————————————————————————————————————————

void PhysicsSystem::cleanUp()
{
	stop();
}

//————————————————————————————————————————————————————————————————————————————————————————

bit PhysicsSystem::isRunnning()
{
	return isPhysicsRunning;
}

//————————————————————————————————————————————————————————————————————————————————————————

bit PhysicsSystem::init(Game* game)
{
	if(!isPhysicsInited)
	{
		this->game = game;
		this->isPhysicsRunning = true;
		if(physicsThreadSignal)
		{
			CloseHandle(physicsThreadSignal);
			physicsThreadSignal = NULL;
		}
		physicsThreadSignal	= CreateEvent(NULL,TRUE,FALSE,NULL);
		if(physicsThreadSignal)
		{
			physicsThread = CreateThread(NULL,4*1024*1024,physicsThreadProc,this,0,NULL);
			if(physicsThread)
			{
				isPhysicsInited = true;
				return true;
			}
		}
		this->isPhysicsRunning = false;
		return false;
	}
	return true;
}

//————————————————————————————————————————————————————————————————————————————————————————

DWORD WINAPI PhysicsSystem::physicsThreadProc( LPVOID params )
{
	PhysicsSystem* This = (PhysicsSystem*)params;

	hkThreadMemory threadMemory(&hkMemory::getInstance());
	hkBaseSystem::initThread(&threadMemory);

	char* stackBuffer;
	int stackSize = 8*1024*1024; 
	stackBuffer = hkAllocate<char>( stackSize, HK_MEMORY_CLASS_BASE);
	threadMemory.setStackArea( stackBuffer, stackSize);

	u64 usedtick       = 0;
	u32 currentFrame   = 0;
	u32 framePerSecond = 60;
	u32 timeElapsed    = 1000/60;
	LARGE_INTEGER starttick;
	LARGE_INTEGER tick;
	LARGE_INTEGER tickPerSecond;
	QueryPerformanceFrequency(&tickPerSecond);
	QueryPerformanceCounter(&tick);

	while(This->isPhysicsRunning)
	{
		u32 result = WaitForSingleObject(This->physicsThreadSignal,INFINITE);
		if(result == WAIT_OBJECT_0 && This->isPhysicsRunning && This->scene)
		{
			QueryPerformanceCounter(&starttick);
						
			This->lastTimeElapsedMs = (u32)clampValue((f32)timeElapsed,10.0f,100.0f);
			This->scene->update(This->lastTimeElapsedMs);
			This->scene->getWorld()->lock();
			This->scene->getWorld()->stepDeltaTime((f32)This->lastTimeElapsedMs/1000.0f);
			This->scene->getWorld()->unlock();
			This->scene->getDebugger()->step(This->lastTimeElapsedMs);
			currentFrame++;
			u64 lasttick = tick.QuadPart;
			u32 frameleft = framePerSecond - currentFrame;

			QueryPerformanceCounter(&tick);

			if( ((usedtick+(tick.QuadPart - lasttick)) < (u64)tickPerSecond.QuadPart) && frameleft)
			{			
				u64 deltatick = tick.QuadPart - starttick.QuadPart;
				usedtick     += tick.QuadPart - lasttick;
				u64 tickleft  = tickPerSecond.QuadPart - usedtick;
				u64 sleeptick = tickleft/frameleft;
				timeElapsed   = (u32)(1000*sleeptick/tickPerSecond.QuadPart);	

				Sleep(timeElapsed);
			}
			else
			{
				usedtick = 0;
				currentFrame = 0;
				frameleft = framePerSecond;
				timeElapsed = 1000/60;
			}
		}
	}

	if(This->scene)
	{
		This->scene->cleanUp();
	}

	threadMemory.setStackArea(0, 0);
	hkDeallocate(stackBuffer);
	hkBaseSystem::clearThreadResources();
	
	return 0;
}

//————————————————————————————————————————————————————————————————————————————————————————

void PhysicsSystem::run( PhysicsScene* scene )
{
	if(isPhysicsInited)
	{
		this->scene = scene;		
		SetEvent(physicsThreadSignal);
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

void PhysicsSystem::stop()
{
	if(isPhysicsInited)
	{
		this->isPhysicsRunning = false;
		SetEvent(physicsThreadSignal);
		if(WaitForSingleObject(physicsThread,1000) == WAIT_TIMEOUT)
		{
			TerminateThread(physicsThread,1);
		}
		CloseHandle(physicsThreadSignal);
		physicsThreadSignal = NULL;
		physicsThread = NULL;
		isPhysicsInited = false;
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

PhysicsScene* PhysicsSystem::getScene()
{
	return scene;
}

//————————————————————————————————————————————————————————————————————————————————————————

u32 PhysicsSystem::getLastTimeElapsed()
{
	return lastTimeElapsedMs;
}