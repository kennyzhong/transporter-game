#ifndef PHYSICSSCENE_H
#define PHYSICSSCENE_H
#include "transporter.h"

class PhysicsScene
{
protected : hkpWorld* physicsWorld;
			bit isSceneInited;
			Game* game;
			hkpPhysicsContext* physicsContext;
			hkVisualDebugger* physicsVDB;
public    : PhysicsScene();
			~PhysicsScene();

			bit init(Game* game);
			hkpWorld* getWorld();
			hkpPhysicsContext* getContext();
			hkVisualDebugger* getDebugger();
			void update(u32 timeStepMs);
			void cleanUp();
			void lock();
			void unlock();
};
#endif