#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H
#include "transporter.h"

class PhysicsSystem
{
protected : void cleanUp();
			HANDLE physicsThread;
			HANDLE physicsThreadSignal;
			static DWORD WINAPI physicsThreadProc(LPVOID params);			
			bit isPhysicsRunning;
			bit isPhysicsInited;
			u32 lastTimeElapsedMs;
			PhysicsScene* scene;						
			Game* game;
public    : PhysicsSystem();
			~PhysicsSystem();
			bit init(Game* game);
			u32 getLastTimeElapsed();
			void stop();
			void run(PhysicsScene* scene);
			PhysicsScene* getScene();

			bit isRunnning();
};
#endif