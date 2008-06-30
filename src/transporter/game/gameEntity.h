#ifndef GAMEENTITY_H
#define GAMEENTITY_H
#include "transporter.h"

class GameEntity 
{
protected : Ogre::Entity* visualEntity;			
			hkpRigidBody* physicsEntity;
			Game* game;
public    : GameEntity(Game* game);
			virtual ~GameEntity();
			Ogre::Entity* getVisualEntity();
			hkpRigidBody* getPhysicsEntity();
			Game* getGame();
			virtual bit init(str name);
};
#endif