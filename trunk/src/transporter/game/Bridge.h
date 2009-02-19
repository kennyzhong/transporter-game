#ifndef BRIDGE_H
#define BRIDGE_H
#include "transporter.h"

class Bridge : public GameEntity
{
protected : virtual void updatePhysics(u32 timeElapse);
			virtual void updateVisual();
			SceneNode* createObject(SceneNode* parentNode,str name,str matName,str meshName,
				                    Ogre::Vector3 pos = Ogre::Vector3::ZERO,
									Ogre::Quaternion rot = Ogre::Quaternion::IDENTITY);
public    : Bridge(Game* game);
			virtual ~Bridge();
			virtual bit init(str name);
};
#endif