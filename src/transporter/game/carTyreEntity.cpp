#include "transporter.h"

CarTyreEntity::CarTyreEntity( CarEntity* car )
:GameEntity(car->getGame())
{
	this->car = car;
}

//————————————————————————————————————————————————————————————————————————————————————————

CarTyreEntity::~CarTyreEntity()
{

}

//————————————————————————————————————————————————————————————————————————————————————————

bit CarTyreEntity::init(str name,str meshName,str rubberMeshName,const Ogre::Vector3& pos,const Ogre::Quaternion& orient)
{
	visualEntity = game->visualSystem.getSceneMgr()->createEntity(name+"Rim",meshName);
	visualEntity->setMaterialName("TyreRimMaterial");
	visualEntity->setCastShadows(true);

	rubberTyre = game->visualSystem.getSceneMgr()->createEntity(name+"Rubber",rubberMeshName);
	rubberTyre->setMaterialName("TyreRubberMaterial");
	rubberTyre->setCastShadows(true);

	Ogre::SceneNode* JointNode = car->getVisualEntity()->getParentSceneNode()->createChildSceneNode(name+"JointNode",pos,orient);	
	Ogre::SceneNode* TyreNode = JointNode->createChildSceneNode(name+"Node");
	TyreNode->attachObject(visualEntity);
	TyreNode->attachObject(rubberTyre);

	return true;
}