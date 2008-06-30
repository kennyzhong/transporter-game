#include "transporter.h"

PhysicsSystem::PhysicsSystem()
{
	isPhysicsRunning = false;
	isPhysicsInited = false;
	physicsWorld = NULL;
	game = NULL;
}

PhysicsSystem::~PhysicsSystem()
{
	cleanUp();
}

void PhysicsSystem::cleanUp()
{
	if(physicsWorld)
	{
		//delete physicsWorld;
		physicsWorld = NULL;
	}
}

bit PhysicsSystem::isRunnning()
{
	return isPhysicsRunning;
}

bit PhysicsSystem::init(Game* game)
{
	this->game = game;

	hkpWorldCinfo info;
	info.m_collisionTolerance = 0.1f;
	info.m_gravity.set(0.0f, -9.8f, 0.0f);
	info.setBroadPhaseWorldSize(1000.0f) ;
	info.setupSolverInfo(hkpWorldCinfo::SOLVER_TYPE_4ITERS_MEDIUM);

	physicsWorld = new hkpWorld(info);

	return true;
}