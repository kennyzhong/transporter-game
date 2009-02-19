#include "transporter.h"

Crate::Crate( Game* game ) : GameEntity(game)
{

}

Crate::~Crate()
{

}

bit Crate::init( str name )
{
	if(isEntityInited)
	{
		return true;
	}
	game->visualSystem.lockThread();
	{	
		visualEntity = game->visualSystem.getSceneMgr()->createEntity(name,Ogre::SceneManager::PrefabType::PT_CUBE);		
		visualEntity->setMaterialName("crate");
		visualEntity->getMesh()->buildTangentVectors();	
		Ogre::SceneNode* node = game->visualSystem.getSceneMgr()->getRootSceneNode()->createChildSceneNode(name+"Node");
		node->attachObject(visualEntity);
		node->setVisible(true);
		node->setScale(0.007425,0.007425,0.007425);
		node->setPosition(-5.5,0.025f,0.0f);
	}
	game->visualSystem.unlockThread();

	hkpRigidBodyCinfo info;
	info.m_motionType = hkpMotion::MOTION_BOX_INERTIA;
	info.m_restitution = 0.025f;
	info.m_shape = new hkpBoxShape(hkVector4(0.25,0.25,0.25));
	info.m_mass = 2.5f;	
	info.m_friction = 0.95f;
	info.m_position.set(0.0f, 0.0f, 0.0f);
	physicsEntity = new hkpRigidBody(info);

	game->gameScene.physicsWorld.getWorld()->lock();
	game->gameScene.physicsWorld.getWorld()->addEntity(physicsEntity, HK_ENTITY_ACTIVATION_DO_ACTIVATE );
	game->gameScene.physicsWorld.getWorld()->unlock();

	isEntityInited = true;
	return true;
}

void Crate::updatePhysics( u32 timeElapse )
{

}

void Crate::updateVisual()
{
	hkVector4 vpos = physicsEntity->getPosition();
	hkQuaternion vOrient = physicsEntity->getRotation();

	Ogre::SceneNode* node = visualEntity->getParentSceneNode();
	node->setPosition(vpos(0),vpos(1),vpos(2));
	node->setOrientation(vOrient(3),vOrient(0),vOrient(1),vOrient(2));
}