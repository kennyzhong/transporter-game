#include "transporter.h"

PhysicsScene::PhysicsScene()
{
	physicsWorld = NULL;
	game = NULL;
	isSceneInited = false;
}

//————————————————————————————————————————————————————————————————————————————————————————

PhysicsScene::~PhysicsScene()
{
	cleanUp();
	if(physicsWorld)
	{
		//delete physicsWorld;
		physicsWorld = NULL;
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

hkpWorld* PhysicsScene::getWorld()
{
	return physicsWorld;
}

//————————————————————————————————————————————————————————————————————————————————————————

bit PhysicsScene::init( Game* game )
{
	if(isSceneInited)
	{
		return true;
	}

	this->game = game;

	hkpWorldCinfo info;
	info.m_collisionTolerance = 0.1f;
	info.m_gravity.set(0.0f, -9.8f, 0.0f);
	info.setBroadPhaseWorldSize(1000.0f) ;
	info.setupSolverInfo(hkpWorldCinfo::SOLVER_TYPE_4ITERS_MEDIUM);

	physicsWorld = new hkpWorld(info);
	isSceneInited = true;

	return true;
}

//————————————————————————————————————————————————————————————————————————————————————————

void PhysicsScene::update()
{
	//TODO: update all entities force
}

//————————————————————————————————————————————————————————————————————————————————————————

void PhysicsScene::cleanUp()
{
	//TODO: clear all entities
}