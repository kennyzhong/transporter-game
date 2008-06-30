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
			PhysicsScene* scene;
			Game* game;
public    : PhysicsSystem();
			~PhysicsSystem();
			bit init(Game* game);
			void stop();
			void run(PhysicsScene* scene);

			bit isRunnning();
};
#endif