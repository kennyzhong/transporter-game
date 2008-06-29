#include "transporter.h"

bit Surface::init(str name)
{
	Ogre::Plane surfacePlane;
	surfacePlane.normal = Ogre::Vector3::UNIT_Y;
	surfacePlane.d = 0;
	Ogre::MeshManager::getSingleton().createPlane(name+"Mesh",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		surfacePlane,
		1000, 1000, 100, 100, true, 1, 100, 100, Ogre::Vector3::UNIT_Z);

	Ogre::SceneNode* surfaceNode = visualSystem->getSceneMgr()->getRootSceneNode()->createChildSceneNode();
	visualEntity  = visualSystem->getSceneMgr()->createEntity( name, name+"Mesh" );
	visualEntity->setMaterialName("asphalt");
	surfaceNode->attachObject(visualEntity);
	surfaceNode->setPosition(0,0,0);

	return true;
}

//————————————————————————————————————————————————————————————————————————————————————————

Surface::Surface( VisualSystem* visual )
:GameEntity(visual)
{

}

//————————————————————————————————————————————————————————————————————————————————————————

Surface::~Surface()
{

}