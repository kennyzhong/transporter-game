#ifndef PHYSICSSCENE_H
#define PHYSICSSCENE_H
#include "transporter.h"

class PhysicsScene
{
protected : hkpWorld* physicsWorld;
			bit isSceneInited;
			Game* game;
public    : PhysicsScene();
			~PhysicsScene();

			bit init(Game* game);
			hkpWorld* getWorld();
			void update(u32 timeStepMs);
			void cleanUp();
			void lock();
			void unlock();
};
#endif