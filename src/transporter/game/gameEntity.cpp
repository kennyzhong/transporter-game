#include "transporter.h"

GameEntity::GameEntity( VisualSystem* visual )
{
	this->visualEntity = NULL;
	this->visualSystem = visual;
}

//————————————————————————————————————————————————————————————————————————————————————————

Ogre::Entity* GameEntity::getVisualEntity()
{
	return this->visualEntity; 
}

//————————————————————————————————————————————————————————————————————————————————————————

VisualSystem* GameEntity::getVisualSystem()
{
	return this->visualSystem;
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
}