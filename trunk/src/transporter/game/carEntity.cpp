#include "transporter.h"

CarEntity::CarEntity( Surface* surface )
:GameEntity(surface->getGame())
{
	this->surface = surface;
}

//————————————————————————————————————————————————————————————————————————————————————————

bit CarEntity::init(str name)
{
	//visualEntity initialization
	{
		Ogre::SceneNode* surfaceNode = surface->getVisualEntity()->getParentSceneNode();

		Ogre::Quaternion orient;
		Ogre::Vector3 pos;

		orient.FromAngleAxis(Ogre::Degree(-90.0f),Ogre::Vector3(1.0f,0.0f,0.0f));
		pos = Ogre::Vector3(0.0f,0.9f,0.0f);

		Ogre::SceneNode* carNode = surfaceNode->createChildSceneNode(name+"Node",pos,orient);
		carNode->setScale(0.35f,0.35f,0.35f);
		visualEntity = game->visualSystem.getSceneMgr()->createEntity(name,"camaro.mesh");	
		visualEntity->setMaterialName("carMaterial");
		carNode->attachObject(visualEntity);	

		orient.FromAngleAxis(Ogre::Degree(180.0f),Ogre::Vector3(0.0f,0.0f,1.0f));
		pos = Ogre::Vector3(-3.0f,-4.8f,-1.5f);
		Ogre::SceneNode* tyreFRNode = carNode->createChildSceneNode(name+"TyreFRNode",pos,orient);
		tyre[0] = new CarTyreEntity(this->game);
		tyre[0]->init("TyreFR");	
		tyreFRNode->setScale(0.85f,0.85f,0.85f);
		tyreFRNode->attachObject(tyre[0]->getVisualEntity());

		pos = Ogre::Vector3(3.0f,-4.8f,-1.5f);
		Ogre::SceneNode* tyreFLNode = carNode->createChildSceneNode(name+"TyreFLNode",pos);
		tyre[1] = new CarTyreEntity(this->game);
		tyre[1]->init("TyreFL");
		tyreFLNode->setScale(0.85f,0.85f,0.85f);
		tyreFLNode->attachObject(tyre[1]->getVisualEntity());

		orient.FromAngleAxis(Ogre::Degree(180.0f),Ogre::Vector3(0.0f,0.0f,1.0f));
		pos = Ogre::Vector3(-3.0f,4.0f,-1.5f);	
		Ogre::SceneNode* tyreRRNode = carNode->createChildSceneNode(name+"TyreRRNode",pos,orient);
		tyre[2] = new CarTyreEntity(this->game);
		tyre[2]->init("TyreRR");
		tyreRRNode->setScale(1.1f,0.9f,0.9f);
		tyreRRNode->attachObject(tyre[2]->getVisualEntity());

		pos = Ogre::Vector3(3.0f,4.0f,-1.5f);
		Ogre::SceneNode* tyreRLNode = carNode->createChildSceneNode(name+"TyreRLNode",pos);
		tyre[3] = new CarTyreEntity(this->game);
		tyre[3]->init("TyreRL");
		tyreRLNode->setScale(1.1f,0.9f,0.9f);	
		tyreRLNode->attachObject(tyre[3]->getVisualEntity());
	}

	//physicsEntity initialization
	{
		VehicleSetup setup;
		hkpConvexVerticesShape* chassisShape = createChassisShape(); 

		int chassisLayer = 1;

		hkpRigidBodyCinfo chassisInfo;
		chassisInfo.m_mass = 750.0f;	
		chassisInfo.m_shape = chassisShape;
		chassisInfo.m_friction = 0.8f;
		chassisInfo.m_motionType = hkpMotion::MOTION_BOX_INERTIA;
		chassisInfo.m_position.set(0.0f, 1.0f, 0.0f);
		chassisInfo.m_inertiaTensor.setDiagonal(1.0f, 1.0f, 1.0f);
		chassisInfo.m_centerOfMass.set( -0.037f, 0.143f, 0.0f);
		chassisInfo.m_collisionFilterInfo = hkpGroupFilter::calcFilterInfo( chassisLayer, 0 );

		physicsEntity = new hkpRigidBody(chassisInfo);
		game->gameScene.physicsWorld.getWorld()->addEntity(physicsEntity, HK_ENTITY_ACTIVATION_DO_ACTIVATE );

		hkVector4 rotationAxis(1.0f, 0.0f, 0.0f); 	 
		hkVector4 upAxis(0.0f, 1.0f, 0.0f); 	 
		physicsActionReorient = new hkpReorientAction(physicsEntity, rotationAxis, upAxis); 	 

		physicsVehicleInstance = new hkpVehicleInstance(physicsEntity);
		setup.buildVehicle(game->gameScene.physicsWorld.getWorld(),*physicsVehicleInstance);
		game->gameScene.physicsWorld.getWorld()->addAction(physicsVehicleInstance);

		physicsEntity->removeReference();
		chassisShape->removeReference();
	}

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
	if(physicsActionReorient)
	{
		physicsActionReorient->removeReference();
		physicsActionReorient = NULL;
	}
	if(physicsVehicleInstance)
	{
		physicsVehicleInstance->removeReference();
		physicsVehicleInstance = NULL;
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

hkpConvexVerticesShape* CarEntity::createChassisShape()
{
	hkReal xSize = 1.75f;
	hkReal ySize = 0.25f;
	hkReal zSize = 1.1f;

	hkReal xBumper = 1.9f;
	hkReal yBumper = 0.15f;
	hkReal zBumper = 1.0f;

	hkReal xRoofFront = 0.4f;
	hkReal xRoofBack = -1.0f;
	hkReal yRoof = ySize + 0.45f;
	hkReal zRoof = 0.7f;

	hkReal xDoorFront = xRoofFront;
	hkReal xDoorBack = xRoofBack;
	hkReal yDoor = ySize;
	hkReal zDoor = zSize + 0.1f;

	int numVertices = 22;

	// 16 = 4 (size of "each float group", 3 for x,y,z, 1 for padding) * 4 (size of float).
	int stride = sizeof(float) * 4;

	float vertices[] = { 
		xSize, ySize, zSize, 0.0f,		// v0
		xSize, ySize, -zSize, 0.0f,		// v1
		xSize, -ySize, zSize, 0.0f,		// v2
		xSize, -ySize, -zSize, 0.0f,	// v3
		-xSize, -ySize, zSize, 0.0f,	// v4
		-xSize, -ySize, -zSize, 0.0f,	// v5

		xBumper, yBumper, zBumper, 0.0f,	// v6
		xBumper, yBumper, -zBumper, 0.0f,	// v7
		-xBumper, yBumper, zBumper, 0.0f,	// v8
		-xBumper, yBumper, -zBumper, 0.0f,	// v9

		xRoofFront, yRoof, zRoof, 0.0f,		// v10
		xRoofFront, yRoof, -zRoof, 0.0f,	// v11
		xRoofBack, yRoof, zRoof, 0.0f,		// v12
		xRoofBack, yRoof, -zRoof, 0.0f,		// v13

		xDoorFront, yDoor, zDoor, 0.0f,		// v14
		xDoorFront, yDoor, -zDoor, 0.0f,	// v15
		xDoorFront, -yDoor, zDoor, 0.0f,	// v16
		xDoorFront, -yDoor, -zDoor, 0.0f,	// v17

		xDoorBack, yDoor, zDoor, 0.0f,		// v18
		xDoorBack, yDoor, -zDoor, 0.0f,		// v19
		xDoorBack, -yDoor, zDoor, 0.0f,		// v20
		xDoorBack, -yDoor, -zDoor, 0.0f,	// v21
	};

	// SHAPE CONSTRUCTION.
	hkpConvexVerticesShape* chassisShape;
	hkArray<hkVector4> planeEquations;
	hkGeometry geom;
	{
		hkStridedVertices stridedVerts;
		{
			stridedVerts.m_numVertices = numVertices;
			stridedVerts.m_striding = stride;
			stridedVerts.m_vertices = vertices;
		}

		hkpGeometryUtility::createConvexGeometry( stridedVerts, geom, planeEquations );
		{
			stridedVerts.m_numVertices = geom.m_vertices.getSize();
			stridedVerts.m_striding = sizeof(hkVector4);
			stridedVerts.m_vertices = &(geom.m_vertices[0](0));
		}

		chassisShape = new hkpConvexVerticesShape(stridedVerts, planeEquations);
	}
	chassisShape->setRadius(0.1f);

	return chassisShape;
}