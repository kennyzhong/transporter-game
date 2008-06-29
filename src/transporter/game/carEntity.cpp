#include "transporter.h"

CarEntity::CarEntity( Surface* surface )
:GameEntity(surface->getVisualSystem())
{
	this->surface = surface;
}

//————————————————————————————————————————————————————————————————————————————————————————

bit CarEntity::init(str name)
{
	Ogre::SceneNode* surfaceNode = surface->getVisualEntity()->getParentSceneNode();

	Ogre::Quaternion orient;
	Ogre::Vector3 pos;

	orient.FromAngleAxis(Ogre::Degree(-90.0f),Ogre::Vector3(1.0f,0.0f,0.0f));
	pos = Ogre::Vector3(0.0f,0.9f,0.0f);

	Ogre::SceneNode* carNode = surfaceNode->createChildSceneNode(name+"Node",pos,orient);
	carNode->setScale(0.35f,0.35f,0.35f);
	visualEntity = visualSystem->getSceneMgr()->createEntity(name,"camaro.mesh");	
	visualEntity->setMaterialName("carMaterial");
	carNode->attachObject(visualEntity);	

	orient.FromAngleAxis(Ogre::Degree(180.0f),Ogre::Vector3(0.0f,0.0f,1.0f));
	pos = Ogre::Vector3(-3.0f,-4.8f,-1.5f);
	Ogre::SceneNode* tyreFRNode = carNode->createChildSceneNode(name+"TyreFRNode",pos,orient);
	tyre[0] = new CarTyreEntity(this->visualSystem);
	tyre[0]->init("TyreFR");	
	tyreFRNode->setScale(0.85f,0.85f,0.85f);
	tyreFRNode->attachObject(tyre[0]->getVisualEntity());

	pos = Ogre::Vector3(3.0f,-4.8f,-1.5f);
	Ogre::SceneNode* tyreFLNode = carNode->createChildSceneNode(name+"TyreFLNode",pos);
	tyre[1] = new CarTyreEntity(this->visualSystem);
	tyre[1]->init("TyreFL");
	tyreFLNode->setScale(0.85f,0.85f,0.85f);
	tyreFLNode->attachObject(tyre[1]->getVisualEntity());

	orient.FromAngleAxis(Ogre::Degree(180.0f),Ogre::Vector3(0.0f,0.0f,1.0f));
	pos = Ogre::Vector3(-3.0f,4.0f,-1.5f);	
	Ogre::SceneNode* tyreRRNode = carNode->createChildSceneNode(name+"TyreRRNode",pos,orient);
	tyre[2] = new CarTyreEntity(this->visualSystem);
	tyre[2]->init("TyreRR");
	tyreRRNode->setScale(1.1f,0.9f,0.9f);
	tyreRRNode->attachObject(tyre[2]->getVisualEntity());

	pos = Ogre::Vector3(3.0f,4.0f,-1.5f);
	Ogre::SceneNode* tyreRLNode = carNode->createChildSceneNode(name+"TyreRLNode",pos);
	tyre[3] = new CarTyreEntity(this->visualSystem);
	tyre[3]->init("TyreRL");
	tyreRLNode->setScale(1.1f,0.9f,0.9f);	
	tyreRLNode->attachObject(tyre[3]->getVisualEntity());

	return true;
}

//————————————————————————————————————————————————————————————————————————————————————————

CarEntity::~CarEntity()
{
	for(u32 i=0 ; i<4 ; i++)
	{
		if(tyre[i])
		{
			delete tyre[i];
			tyre[i] = NULL;
		}
	}
}
