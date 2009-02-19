#include "transporter.h"

GameEntity::GameEntity( Game* game )
{
	this->visualEntity = NULL;
	this->physicsEntity = NULL;
	this->isEntityInited = false;
	this->game = game;
}

//————————————————————————————————————————————————————————————————————————————————————————

Ogre::Entity* GameEntity::getVisualEntity()
{
	return this->visualEntity; 
}

//————————————————————————————————————————————————————————————————————————————————————————

bit GameEntity::init(str name)
{	
	return true;
}

//————————————————————————————————————————————————————————————————————————————————————————

GameEntity::~GameEntity()
{
	if(visualEntity)
	{		
		if(visualEntity->getParentSceneNode())
		{
			visualEntity->getParentSceneNode()->detachObject(visualEntity);
		}
		delete visualEntity;
		visualEntity = NULL;
	}
	//TODO: delete physics entity
}

//————————————————————————————————————————————————————————————————————————————————————————

hkpRigidBody* GameEntity::getPhysicsEntity()
{
	return this->physicsEntity;
}

//————————————————————————————————————————————————————————————————————————————————————————

Game* GameEntity::getGame()
{
	return game;
}

//————————————————————————————————————————————————————————————————————————————————————————

void GameEntity::update( u32 evId,u32 param )
{
	if(isEntityInited)
	{
		if(evId == EV_UPDATE_PHYSICS_FORCE)
		{
			updatePhysics(param);
		}
		else if(evId == EV_UPDATE_VISUAL_ENTITIES)
		{
			updateVisual();
		}
	}
}

void GameEntity::updatePhysics( u32 timeElapse )
{

}

void GameEntity::updateVisual()
{

}