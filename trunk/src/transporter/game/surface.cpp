#include "transporter.h"

bit Surface::init(str name)
{
	if(isEntityInited)
	{
		return true;
	}
	
	//Physics entity initializations
	{
		hkpRigidBodyCinfo surfaceInfo;
		physicsSurfaceShape = new PhysicsFlatLand(100);
		surfaceInfo.m_shape = (hkpShape*)physicsSurfaceShape->createMoppShape();
		surfaceInfo.m_position.set(0.0f,0.0f,0.0f);
		surfaceInfo.m_motionType = hkpMotion::MOTION_FIXED;
		surfaceInfo.m_friction = 0.55f;

		physicsEntity = new hkpRigidBody(surfaceInfo);
		game->gameScene.physicsWorld.getWorld()->lock();
		game->gameScene.physicsWorld.getWorld()->addEntity(physicsEntity);
		game->gameScene.physicsWorld.getWorld()->unlock();

		physicsEntity->removeReference();
		surfaceInfo.m_shape->removeReference();		
	}

	game->visualSystem.lockThread();
	{
		Ogre::Plane surfacePlane;
		surfacePlane.normal = Ogre::Vector3::UNIT_Y;
		surfacePlane.d = 0;
		Ogre::MeshManager::getSingleton().createPlane(name+"Mesh",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			surfacePlane,
			2000, 2000, 200, 200, true, 1, 400, 400, Ogre::Vector3::UNIT_Z);
		
		Ogre::SceneNode* surfaceNode = game->visualSystem.getSceneMgr()->getRootSceneNode()->createChildSceneNode();
		visualEntity  = game->visualSystem.getSceneMgr()->createEntity( name, name+"Mesh" );
		visualEntity->setMaterialName("asphalt");	
		visualEntity->setCastShadows(false);
		//visualEntity->setVisible(false);
		surfaceNode->attachObject(visualEntity);
		surfaceNode->setPosition(0.0f,0.0f,0.0f);			
	}
	game->visualSystem.unlockThread();

	isEntityInited = true;
	return true;
}

//————————————————————————————————————————————————————————————————————————————————————————

Surface::Surface( Game* game )
:GameEntity(game)
{
	physicsSurfaceShape = NULL;
}

//————————————————————————————————————————————————————————————————————————————————————————

Surface::~Surface()
{
	if(physicsSurfaceShape)
	{
		delete physicsSurfaceShape;
		physicsSurfaceShape = NULL;
	}
}