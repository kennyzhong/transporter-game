#include "transporter.h"

Bridge::Bridge( Game* game ) : GameEntity(game)
{

}

Bridge::~Bridge()
{

}

bit Bridge::init( str name )
{
	if(isEntityInited)
	{
		return true;
	}
	game->visualSystem.lockThread();
	{
	Ogre::SceneNode* rootNode = game->visualSystem.getSceneMgr()->getRootSceneNode()->createChildSceneNode("roadSurface",Ogre::Vector3(0.0f,23.545,0.0f));

	createObject(rootNode,"SouthStructure","BridgeMaterial#27","BridgeStructure.mesh",Ogre::Vector3(-33.9961,-67.5836,927.86));
	createObject(rootNode,"NorthStructure","BridgeMaterial#27","BridgeStructure.mesh",Ogre::Vector3(-33.9961,-67.5836,-892.044));

	createObject(rootNode,"NorthRightTower","BridgeMaterial#27","BridgeTower.mesh",Ogre::Vector3(14.5168,-90.5743,-466.628));
	createObject(rootNode,"SouthLeftTower","BridgeMaterial#27","BridgeTower.mesh",Ogre::Vector3(-12.1081,-90.5743,503.136));
	createObject(rootNode,"NorthLeftTower","BridgeMaterial#27","BridgeTower.mesh",Ogre::Vector3(-12.1081,-90.5743,-466.628));
	createObject(rootNode,"SouthRightTower","BridgeMaterial#27","BridgeTower.mesh",Ogre::Vector3(14.5168,-90.5743,503.136));

	createObject(rootNode,"NorthBase","BridgeBridgeFoundationMat","BridgeBase.mesh",Ogre::Vector3(1.20435,-122.031,-466.732));
	createObject(rootNode,"SouthBase","BridgeBridgeFoundationMat","BridgeBase.mesh",Ogre::Vector3(1.20435,-122.031,503.031));

	createObject(rootNode,"NorthFoundation","BridgeBridgeFoundationMat","Foundation.mesh",Ogre::Vector3(1.20435,-115.691,-466.688));
	createObject(rootNode,"SouthFoundation","BridgeBridgeFoundationMat","Foundation.mesh",Ogre::Vector3(1.20435,-115.691,503.075));

	createObject(rootNode,"SouthColumnLeftFront","BridgeBridgeColumnMat","ColumnLeft.mesh",Ogre::Vector3(-16.8817,-122.031,815.781));
	createObject(rootNode,"SouthColumnRightFront","BridgeBridgeColumnMat","ColumnRight.mesh",Ogre::Vector3(19.0129,-122.031,815.781));
	createObject(rootNode,"SouthColumnRightRear","BridgeBridgeColumnMat","ColumnRight.mesh",Ogre::Vector3(19.0129,-122.031,965.755));
	createObject(rootNode,"SouthColumnLeftRear","BridgeBridgeColumnMat","ColumnLeft.mesh",Ogre::Vector3(-16.8817,-122.031,965.755));

	createObject(rootNode,"NorthColumnRightFront","BridgeBridgeColumnMat","ColumnRight.mesh",Ogre::Vector3(19.0129,-122.031,-929.939));
	createObject(rootNode,"NorthColumnLeftFront","BridgeBridgeColumnMat","ColumnLeft.mesh",Ogre::Vector3(-16.8817,-122.031,-929.939));
	createObject(rootNode,"NorthColumnLeftRear","BridgeBridgeColumnMat","ColumnLeft.mesh",Ogre::Vector3(-16.8817,-122.031,-779.965));
	createObject(rootNode,"NorthColumnRightRear","BridgeBridgeColumnMat","ColumnRight.mesh",Ogre::Vector3(19.0129,-122.031,-779.965));

	createObject(rootNode,"NorthIsland","BridgeBridgeIslandMat","NorthIsland.mesh",Ogre::Vector3(-57.6726,-94.3464,-918.976));
	createObject(rootNode,"SouthIsland","BridgeBridgeIslandMat","SouthIsland.mesh",Ogre::Vector3(-57.6726,-94.3464,952.714));

	createObject(rootNode,"BarrierLeft","BridgeBridgeBarrierMat","BridgeBarrier.mesh",Ogre::Vector3(-10.8955,-23.7755,17.7291));
	createObject(rootNode,"BarrierRight","BridgeBridgeBarrierMat","BridgeBarrier.mesh",Ogre::Vector3(13.0344,-23.7755,17.7291));

	createObject(rootNode,"MiddleLeftMainCable","BridgeMaterial#27","MiddleMainCable.mesh",Ogre::Vector3(-12.6185,872.278,16.5902));
	createObject(rootNode,"MiddleRightMainCable","BridgeMaterial#27","MiddleMainCable.mesh",Ogre::Vector3(15.0043,872.278,16.5902));
	createObject(rootNode,"SouthRightMainCable","BridgeMaterial#27","SouthMainCable.mesh",Ogre::Vector3(15.7932,610.738,909.801));
	createObject(rootNode,"SouthLeftMainCable","BridgeMaterial#27","SouthMainCable.mesh",Ogre::Vector3(-13.018,610.738,909.801));
	createObject(rootNode,"NorthRightMainCable","BridgeMaterial#27","NorthMainCable.mesh",Ogre::Vector3(15.7933,609.517,-871.872));
	createObject(rootNode,"NorthLeftMainCable","BridgeMaterial#27","NorthMainCable.mesh",Ogre::Vector3(-13.0179,609.517,-871.872));

	createObject(rootNode,"RoadBase1","BridgeBridgeColumnMat","RoadBase.mesh",Ogre::Vector3(15.4112,-29.9113,987.486));
	createObject(rootNode,"RoadBase2","BridgeBridgeColumnMat","RoadBase.mesh",Ogre::Vector3(15.4112,-29.9113,663.818));
	createObject(rootNode,"RoadBase3","BridgeBridgeColumnMat","RoadBase.mesh",Ogre::Vector3(15.4112,-29.9113,341.176));
	createObject(rootNode,"RoadBase4","BridgeBridgeColumnMat","RoadBase.mesh",Ogre::Vector3(15.4112,-29.9113,17.9908));
	createObject(rootNode,"RoadBase5","BridgeBridgeColumnMat","RoadBase.mesh",Ogre::Vector3(15.4112,-29.9113,-305.219));
	createObject(rootNode,"RoadBase6","BridgeBridgeColumnMat","RoadBase.mesh",Ogre::Vector3(15.4112,-29.9113,-628.002));
	createObject(rootNode,"RoadBase7","BridgeBridgeColumnMat","RoadBase.mesh",Ogre::Vector3(15.4112,-29.9113,-951.67));

	createObject(rootNode,"Road1","BridgeBridgeRoadMat","Road.mesh",Ogre::Vector3(1.0542,-24.5548,987.466));
	createObject(rootNode,"Road2","BridgeBridgeRoadMat","Road.mesh",Ogre::Vector3(1.0542,-24.5548,663.808));
	createObject(rootNode,"Road3","BridgeBridgeRoadMat","Road.mesh",Ogre::Vector3(1.0542,-24.5548,341.166));
	createObject(rootNode,"Road4","BridgeBridgeRoadMat","Road.mesh",Ogre::Vector3(1.0542,-24.5548,17.9898));
	createObject(rootNode,"Road5","BridgeBridgeRoadMat","Road.mesh",Ogre::Vector3(1.0542,-24.5548,-305.199));
	createObject(rootNode,"Road6","BridgeBridgeRoadMat","Road.mesh",Ogre::Vector3(1.0542,-24.5548,-628.002));
	createObject(rootNode,"Road7","BridgeBridgeRoadMat","Road.mesh",Ogre::Vector3(1.0542,-24.5548,-951.65));

	createObject(rootNode,"SouthTowerBar3Inside","BridgeMaterial#27","TowerBar3Inside.mesh",Ogre::Vector3(-0.0423242,145.863,503.241));
	createObject(rootNode,"SouthTowerBar5Inside","BridgeMaterial#27","TowerBar5Inside.mesh",Ogre::Vector3(-0.0423242,105.587,503.241));
	createObject(rootNode,"SouthTowerBar6Inside","BridgeMaterial#27","TowerBar6Inside.mesh",Ogre::Vector3(-0.0423242,145.863,503.241));

	createObject(rootNode,"SouthTowerBar2","BridgeMaterial#27","TowerBar2.mesh",Ogre::Vector3(1.2096,-36.0118,501.548));
	createObject(rootNode,"SouthTowerBar3","BridgeMaterial#27","TowerBar3.mesh",Ogre::Vector3(1.20961,32.0648,501.548));
	createObject(rootNode,"SouthTowerBar5","BridgeMaterial#27","TowerBar5.mesh",Ogre::Vector3(1.20961,106.731,501.548));
	createObject(rootNode,"SouthTowerBar6","BridgeMaterial#27","TowerBar6.mesh",Ogre::Vector3(1.20961,147.51,501.548));

	createObject(rootNode,"NorthTowerBar3Inside","BridgeMaterial#27","TowerBar3Inside.mesh",Ogre::Vector3(-0.0423242,29.0416,-466.523));
	createObject(rootNode,"NorthTowerBar5Inside","BridgeMaterial#27","TowerBar5Inside.mesh",Ogre::Vector3(-0.0423242,105.587,-466.523));
	createObject(rootNode,"NorthTowerBar6Inside","BridgeMaterial#27","TowerBar6Inside.mesh",Ogre::Vector3(-0.0423242,145.863,-466.523));

	createObject(rootNode,"NorthTowerBar2","BridgeMaterial#27","TowerBar2.mesh",Ogre::Vector3(1.20961,-36.0118,-468.216));
	createObject(rootNode,"NorthTowerBar3","BridgeMaterial#27","TowerBar3.mesh",Ogre::Vector3(1.20961,32.0648,-468.216));
	createObject(rootNode,"NorthTowerBar5","BridgeMaterial#27","TowerBar5.mesh",Ogre::Vector3(1.20961,106.731,-468.216));
	createObject(rootNode,"NorthTowerBar6","BridgeMaterial#27","TowerBar6.mesh",Ogre::Vector3(1.20961,147.51,-468.216));

	createObject(rootNode,"Line88","BridgeMaterial#27","Line88.mesh",Ogre::Vector3(22.8871,52.47,518.506));
	createObject(rootNode,"Line86","BridgeMaterial#27","Line86.mesh",Ogre::Vector3(22.8871,51.2481,-480.577));

	createObject(rootNode,"Line87","BridgeMaterial#27","Line87.mesh",Ogre::Vector3(-5.92408,52.47,518.506));
	createObject(rootNode,"Line85","BridgeMaterial#27","Line85.mesh",Ogre::Vector3(-5.9241,51.2481,-480.577));

	createObject(rootNode,"Line76","BridgeMaterial#27","Line76.mesh",Ogre::Vector3(14.8245,-13.4304,-29.94658));
	createObject(rootNode,"Line74","BridgeMaterial#27","Line74.mesh",Ogre::Vector3(14.8245,-9.44093,-94.0097));
	createObject(rootNode,"Line71","BridgeMaterial#27","Line71.mesh",Ogre::Vector3(14.8245,-3.9501,-160.152));
	createObject(rootNode,"Line68","BridgeMaterial#27","Line68.mesh",Ogre::Vector3(14.8245,9.20819,-258.205));
	createObject(rootNode,"Line66","BridgeMaterial#27","Line66.mesh",Ogre::Vector3(14.8246,21.1886,-321.652));
	createObject(rootNode,"Line65","BridgeMaterial#27","Line65.mesh",Ogre::Vector3(14.8246,36.2154,-386.543));
	createObject(rootNode,"Line64","BridgeMaterial#27","Line64.mesh",Ogre::Vector3(14.8246,54.3408,-449.256));
	createObject(rootNode,"Line60","BridgeMaterial#27","Line60.mesh",Ogre::Vector3(14.8246,-11.5355,100.069));
	createObject(rootNode,"Line58","BridgeMaterial#27","Line58.mesh",Ogre::Vector3(14.8245,-0.237194,229.241));
	createObject(rootNode,"Line57","BridgeMaterial#27","Line57.mesh",Ogre::Vector3(14.8246,-8.10019,163.304));
	createObject(rootNode,"Line53","BridgeMaterial#27","Line53.mesh",Ogre::Vector3(14.8245,9.20818,294.517));
	createObject(rootNode,"Line51","BridgeMaterial#27","Line51.mesh",Ogre::Vector3(14.8245,21.1886,357.964));
	createObject(rootNode,"Line49","BridgeMaterial#27","Line49.mesh",Ogre::Vector3(14.8245,36.2154,422.855));
	createObject(rootNode,"Line48","BridgeMaterial#27","Line48.mesh",Ogre::Vector3(14.8245,54.3407,485.568));
	createObject(rootNode,"Line47","BridgeMaterial#27","Line47.mesh",Ogre::Vector3(14.8246,-12.9111,32.9579));

	createObject(rootNode,"Line45","BridgeMaterial#27","Line45.mesh",Ogre::Vector3(-12.8355,-11.5355,100.068));
	createObject(rootNode,"Line43","BridgeMaterial#27","Line43.mesh",Ogre::Vector3(-12.8355,-0.237206,229.241));
	createObject(rootNode,"Line42","BridgeMaterial#27","Line42.mesh",Ogre::Vector3(-12.8355,-8.10019,163.304));
	createObject(rootNode,"Line38","BridgeMaterial#27","Line38.mesh",Ogre::Vector3(-12.8355,9.20816,294.517));
	createObject(rootNode,"Line36","BridgeMaterial#27","Line36.mesh",Ogre::Vector3(-12.8355,21.1886,357.964));
	createObject(rootNode,"Line34","BridgeMaterial#27","Line34.mesh",Ogre::Vector3(-12.8355,36.2154,422.855));
	createObject(rootNode,"Line33","BridgeMaterial#27","Line33.mesh",Ogre::Vector3(-12.8355,54.3408,485.569));
	createObject(rootNode,"Line32","BridgeMaterial#27","Line32.mesh",Ogre::Vector3(-12.8355,-12.9111,32.9578));
	createObject(rootNode,"Line30","BridgeMaterial#27","Line30.mesh",Ogre::Vector3(-12.8355,-13.4304,-29.9465));
	createObject(rootNode,"Line28","BridgeMaterial#27","Line28.mesh",Ogre::Vector3(-12.8355,-9.44093,-94.0097));
	createObject(rootNode,"Line26","BridgeMaterial#27","Line26.mesh",Ogre::Vector3(-12.8355,-3.9501,-160.152));
	createObject(rootNode,"Line23","BridgeMaterial#27","Line23.mesh",Ogre::Vector3(-12.8355,9.20819,-258.205));
	createObject(rootNode,"Line21","BridgeMaterial#27","Line21.mesh",Ogre::Vector3(-12.8355,21.1886,-321.652));
	createObject(rootNode,"Line19","BridgeMaterial#27","Line19.mesh",Ogre::Vector3(-12.8355,36.2154,-386.543));
	createObject(rootNode,"Line11","BridgeMaterial#27","Line11.mesh",Ogre::Vector3(-12.8355,54.3408,-449.256));
	}
	game->visualSystem.unlockThread();

	//createObject(rootNode,"BarrierLeft","BridgeBridgeBarrierMat","BridgeBarrier.mesh",Ogre::Vector3(-10.8955,-23.7755,17.7291));
	//createObject(rootNode,"BarrierRight","BridgeBridgeBarrierMat","BridgeBarrier.mesh",Ogre::Vector3(13.0344,-23.7909,17.7291));

	hkpRigidBodyCinfo info;
	info.m_motionType = hkpMotion::MOTION_FIXED;
	info.m_restitution = 0.0f;
	info.m_shape = new hkpBoxShape(hkVector4(0.9,0.9,250));
	info.m_mass = 50.0f;	
	info.m_friction = 5.0f;
	info.m_position.set(-11.475, 0.0, 0.0f);
	physicsEntity = new hkpRigidBody(info);

	info.m_motionType = hkpMotion::MOTION_FIXED;
	info.m_restitution = 0.0f;
	info.m_shape = new hkpBoxShape(hkVector4(0.9,0.9,750));
	info.m_mass = 50.0f;	
	info.m_friction = 5.0f;
	info.m_position.set(13.575, 0.0, 0.0f);
	hkpRigidBody* physicsEntity2 = new hkpRigidBody(info);

	game->gameScene.physicsWorld.getWorld()->lock();
	game->gameScene.physicsWorld.getWorld()->addEntity(physicsEntity, HK_ENTITY_ACTIVATION_DO_ACTIVATE );
	game->gameScene.physicsWorld.getWorld()->addEntity(physicsEntity2, HK_ENTITY_ACTIVATION_DO_ACTIVATE );
	game->gameScene.physicsWorld.getWorld()->unlock();

	isEntityInited = true;
	return true;
}

void Bridge::updatePhysics( u32 timeElapse )
{

}

void Bridge::updateVisual()
{

}

SceneNode* Bridge::createObject( SceneNode* parentNode,str name,str matName,str meshName, 
								Ogre::Vector3 pos /*= Ogre::Vector3::ZERO*/, 
								Ogre::Quaternion rot /*= Ogre::Quaternion::IDENTITY*/ )
{
	SceneNode* node = parentNode->createChildSceneNode(name+"Node",pos,rot);
	Ogre::Entity* entity = game->visualSystem.getSceneMgr()->createEntity(name,meshName);
	entity->setMaterialName(matName);
	entity->setCastShadows(false);
	entity->getMesh()->buildTangentVectors();
	node->attachObject(entity);
	return node;
}