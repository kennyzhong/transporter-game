#include "transporter.h"

GameEntity::GameEntity( Game* game )
{
	this->visualEntity = NULL;
	this->physicsEntity = NULL;
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