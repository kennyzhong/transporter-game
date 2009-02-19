#ifndef GAMEENTITY_H
#define GAMEENTITY_H
#include "transporter.h"

class GameEntity : public UpdateListener
{
protected : Ogre::Entity* visualEntity;			
			hkpRigidBody* physicsEntity;
			bit isEntityInited;
			Game* game;
			virtual void update( u32 evId,u32 param );
			virtual void updatePhysics(u32 timeElapse);
			virtual void updateVisual();
public    : GameEntity(Game* game);
			virtual ~GameEntity();
			Ogre::Entity* getVisualEntity();
			hkpRigidBody* getPhysicsEntity();
			Game* getGame();
			virtual bit init(str name);
};
#endif