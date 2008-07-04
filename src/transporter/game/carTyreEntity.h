#ifndef CARTYREENTITY_H
#define CARTYREENTITY_H
#include "transporter.h"

class CarEntity;

class CarTyreEntity : public GameEntity
{
protected : CarEntity* car;
			Ogre::Entity* rubberTyre;
public    : CarTyreEntity(CarEntity* car);
			virtual ~CarTyreEntity();
			virtual bit init(str name,str meshName,str rubberMeshName,const Ogre::Vector3& pos = Ogre::Vector3::ZERO,
				             const Ogre::Quaternion& orient=Ogre::Quaternion::IDENTITY);
};
#endif