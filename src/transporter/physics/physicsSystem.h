#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H
#include "transporter.h"

class PhysicsSystem
{
protected : void cleanUp();
			hkpWorld* physicsWorld;
			bit isPhysicsRunning;
			bit isPhysicsInited;
			Game* game;
public    : PhysicsSystem();
			~PhysicsSystem();
			bit init(Game* game);

			bit isRunnning();
};
#endif