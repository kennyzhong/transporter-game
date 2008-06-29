#ifndef GAMEENTITY_H
#define GAMEENTITY_H
#include "transporter.h"

class GameEntity 
{
protected : Ogre::Entity* visualEntity;			
			VisualSystem* visualSystem;
public    : GameEntity(VisualSystem* visual);
			virtual ~GameEntity();
			Ogre::Entity* getVisualEntity();
			VisualSystem* getVisualSystem();
			virtual bit init(str name);
};
#endif