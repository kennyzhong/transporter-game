#include "transporter.h"

RoadBarrier::RoadBarrier( Game* game ) : GameEntity(game)
{

}

RoadBarrier::~RoadBarrier()
{

}

bit RoadBarrier::init( str name )
{
	if(isEntityInited)
	{
		return true;
	}
	game->visualSystem.lockThread();
	{	
		visualEntity = game->visualSystem.getSceneMgr()->createEntity(name,"Barrier.mesh");		
		visualEntity->setMaterialName("barrier");
		visualEntity->getMesh()->buildTangentVectors();	
		Ogre::SceneNode* node = game->visualSystem.getSceneMgr()->getRootSceneNode()->createChildSceneNode(name+"Node");
		node->attachObject(visualEntity);
		node->setVisible(true);
		node->setPosition(-5.5,0.025f,0.0f);
	}
	game->visualSystem.unlockThread();

	size_t vertex_count,index_count;
	Vector3* vertices;
	unsigned long* indices;

	getMeshInformation(visualEntity->getMesh().getPointer(),vertex_count,vertices,index_count,indices,
		Ogre::Vector3::ZERO,Ogre::Quaternion::IDENTITY,Ogre::Vector3::UNIT_SCALE);

	hkVector4* phVertices = new hkVector4[index_count];
	for(u32 i=0 ; i<index_count ; i++)
	{
		phVertices[i].set( vertices[indices[i]].x,
			vertices[indices[i]].y,
			vertices[indices[i]].z );
	}

	hkpConvexVerticesShape* barrierShape;
	hkArray<hkVector4> planeEquations;
	hkGeometry geom;
	{
		hkStridedVertices stridedVerts;
		{
			stridedVerts.m_numVertices = index_count;
			stridedVerts.m_striding = sizeof(float) * 4;
			stridedVerts.m_vertices = (float*)phVertices;
		}

		hkpGeometryUtility::createConvexGeometry( stridedVerts, geom, planeEquations );
		{
			stridedVerts.m_numVertices = geom.m_vertices.getSize();
			stridedVerts.m_striding = sizeof(hkVector4);
			stridedVerts.m_vertices = &(geom.m_vertices[0](0));
		}

		barrierShape = new hkpConvexVerticesShape(stridedVerts, planeEquations);
	}	

	delete[] vertices;
	delete[] indices;
	delete[] phVertices;	

	hkpRigidBodyCinfo info;
	info.m_motionType = hkpMotion::MOTION_BOX_INERTIA;
	info.m_restitution = 0.0f;
	info.m_shape = barrierShape;//new hkpBoxShape(hkVector4(0.25,0.5,1.0));
	info.m_mass = 500.0f;	
	info.m_friction = 5.0f;
	info.m_maxLinearVelocity = 5;
	info.m_maxAngularVelocity = 5;
	info.m_position.set(0.0f, 0.0f, 0.0f);
	info.m_centerOfMass.set(0.0,-0.25,0.0);
	physicsEntity = new hkpRigidBody(info);

	game->gameScene.physicsWorld.getWorld()->lock();
	game->gameScene.physicsWorld.getWorld()->addEntity(physicsEntity, HK_ENTITY_ACTIVATION_DO_ACTIVATE );
	game->gameScene.physicsWorld.getWorld()->unlock();

	isEntityInited = true;
	return true;
}

void RoadBarrier::updatePhysics( u32 timeElapse )
{

}

void RoadBarrier::updateVisual()
{
	hkVector4 vpos = physicsEntity->getPosition();
	hkQuaternion vOrient = physicsEntity->getRotation();

	Ogre::SceneNode* node = visualEntity->getParentSceneNode();
	node->setPosition(vpos(0),vpos(1)-0.075f,vpos(2));
	node->setOrientation(vOrient(3),vOrient(0),vOrient(1),vOrient(2));
}