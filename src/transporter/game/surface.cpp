#include "transporter.h"

bit Surface::init(str name)
{
	//visualEntity initialization
	{
		Ogre::Plane surfacePlane;
		surfacePlane.normal = Ogre::Vector3::UNIT_Y;
		surfacePlane.d = 0;
		Ogre::MeshManager::getSingleton().createPlane(name+"Mesh",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			surfacePlane,
			1000, 1000, 100, 100, true, 1, 100, 100, Ogre::Vector3::UNIT_Z);

		Ogre::SceneNode* surfaceNode = game->visualSystem.getSceneMgr()->getRootSceneNode()->createChildSceneNode();
		visualEntity  = game->visualSystem.getSceneMgr()->createEntity( name, name+"Mesh" );
		visualEntity->setMaterialName("asphalt");
		surfaceNode->attachObject(visualEntity);
		surfaceNode->setPosition(0,0,0);
	}
	
	//physicsEntity initialization
	{
		hkpRigidBodyCinfo surfaceInfo;
		physicsSurfaceShape = new PhysicsFlatLand;
		surfaceInfo.m_shape = (hkpShape*)physicsSurfaceShape->createMoppShapeForSpu();
		surfaceInfo.m_position.set(0.0f,0.0f,0.0f);
		surfaceInfo.m_motionType = hkpMotion::MOTION_FIXED;
		surfaceInfo.m_friction = 0.5f;

		physicsEntity = new hkpRigidBody(surfaceInfo);
		game->gameScene.physicsWorld.getWorld()->addEntity(physicsEntity);
		physicsEntity->removeReference();

		surfaceInfo.m_shape->removeReference();
	}

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