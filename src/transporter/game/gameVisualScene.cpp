#include "transporter.h"

GameVisualScene::GameVisualScene()
{

}

//————————————————————————————————————————————————————————————————————————————————————————

GameVisualScene::~GameVisualScene()
{

}

//————————————————————————————————————————————————————————————————————————————————————————

bit GameVisualScene::init( Game* game )
{
	game->visualSystem.lockThread();

	game->visualSystem.loadResources("InGame");
	Ogre::Viewport* vp = game->visualSystem.getPrimaryRenderWindow()->getViewport(0);
	Ogre::CompositorManager* compositorMgr = Ogre::CompositorManager::getSingletonPtr();
	Ogre::CompositorInstance* compositor = compositorMgr->addCompositor(vp,"LuminanceBloom");
	compositorMgr->setCompositorEnabled(vp,"LuminanceBloom",true);

	VisualScene::init(game);

	Ogre::Light* light = game->visualSystem.getSceneMgr()->createLight("MainLight");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setPosition(800,900,-550);
	Ogre::Vector3 dir = -light->getPosition();
	dir.normalise();
	light->setDirection(dir);
	light->setSpecularColour(1.0f,1.0f,1.0f);
	light->setDiffuseColour(0.8f,0.8f,0.8f);
	//light->setSpotlightRange(Ogre::Degree(50), Ogre::Degree(75));
	light->setPowerScale(1.0f);
	light->setCastShadows(true);	

	//Ogre::LiSPSMShadowCameraSetup* cameraSetup = new Ogre::LiSPSMShadowCameraSetup;
	//game->visualSystem.getSceneMgr()->setShadowCameraSetup(Ogre::ShadowCameraSetupPtr(cameraSetup));

	game->visualSystem.getSceneMgr()->getRootSceneNode()->attachObject(light);

	game->visualSystem.getSceneMgr()->setAmbientLight(Ogre::ColourValue(0.1,0.90,0.75));
	//game->visualSystem.getSceneMgr()->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE);
	game->visualSystem.getSceneMgr()->setShadowTextureSize(1024);
	//game->visualSystem.getSceneMgr()->setShadowTextureSettings(1024,2);
	game->visualSystem.getSceneMgr()->setShadowFarDistance(24);
	game->visualSystem.getSceneMgr()->setShadowDirLightTextureOffset(0.05);
	game->visualSystem.getSceneMgr()->setShadowTextureSelfShadow(false);
	game->visualSystem.getSceneMgr()->setShadowColour( Ogre::ColourValue(0.75f, 0.75f, 0.75f) );
	game->visualSystem.getSceneMgr()->setSkyBox(true,"skybox",1000);	
	game->visualSystem.getSceneMgr()->setShadowTextureCasterMaterial("depthShadowMapCasterMaterial");
	//game->visualSystem.getSceneMgr()->setShadowTextureCasterMaterial("VarianceShadowMapping/ShadowCaster");
	game->visualSystem.getSceneMgr()->setShadowTexturePixelFormat(PF_FLOAT32_R);
	game->visualSystem.getSceneMgr()->setShadowCasterRenderBackFaces(true);
	game->visualSystem.getSceneMgr()->setShadowTechnique(SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED);
	
	Bridge* bridge = new Bridge(game);
	bridge->init("bridge");

	RoadBarrier* barrier[20];

	for(u32 i=0 ; i<20 ; i++)
	{		
		barrier[i] = new RoadBarrier(game);
		barrier[i]->init("barrier"+IntToStr(i));		
	}
	hkQuaternion q;
	q.setAxisAngle(hkVector4(0,1,0),Deg2Rad(90));
	barrier[0]->getPhysicsEntity()->setPositionAndRotation(hkVector4(-5.5,0.51f,-50.0),q);
	barrier[1]->getPhysicsEntity()->setPositionAndRotation(hkVector4(4.5,0.51f,-40.0),q);
	barrier[2]->getPhysicsEntity()->setPositionAndRotation(hkVector4(-5.5,0.51f,-30.0),q);
	barrier[3]->getPhysicsEntity()->setPositionAndRotation(hkVector4(1.5,0.51f,-20.0),q);
	barrier[4]->getPhysicsEntity()->setPositionAndRotation(hkVector4(-5.5,0.51f,-10.0),q);
	barrier[5]->getPhysicsEntity()->setPositionAndRotation(hkVector4(2.5,0.51f,-70.0),q);
	barrier[6]->getPhysicsEntity()->setPositionAndRotation(hkVector4(-5.5,0.51f,-90.0),q);
	barrier[7]->getPhysicsEntity()->setPositionAndRotation(hkVector4(0.5,0.51f,100.0),q);
	barrier[8]->getPhysicsEntity()->setPositionAndRotation(hkVector4(-5.5,0.51f,110.0),q);
	barrier[9]->getPhysicsEntity()->setPositionAndRotation(hkVector4(5.5,0.51f,40.0),q);
	barrier[10]->getPhysicsEntity()->setPositionAndRotation(hkVector4(1.5,0.51f,50.0),q);
	barrier[11]->getPhysicsEntity()->setPositionAndRotation(hkVector4(-5.5,0.51f,60.0),q);
	barrier[12]->getPhysicsEntity()->setPositionAndRotation(hkVector4(5.5,0.51f,70.0),q);
	barrier[13]->getPhysicsEntity()->setPositionAndRotation(hkVector4(-5.5,0.51f,80.0),q);
	barrier[14]->getPhysicsEntity()->setPositionAndRotation(hkVector4(3.5,0.51f,90.0),q);
	barrier[15]->getPhysicsEntity()->setPositionAndRotation(hkVector4(-5.5,0.51f,100.0),q);
	barrier[16]->getPhysicsEntity()->setPositionAndRotation(hkVector4(-2.5,0.51f,110.0),q);
	barrier[17]->getPhysicsEntity()->setPositionAndRotation(hkVector4(-0.5,0.51f,120.0),q);
	barrier[18]->getPhysicsEntity()->setPositionAndRotation(hkVector4(2.5,0.51f,130.0),q);
	barrier[19]->getPhysicsEntity()->setPositionAndRotation(hkVector4(5.5,0.51f,140.0),q);

	Crate* crate[32];
	for(u32 i=0 ; i<32 ; i++)
	{
		crate[i] = new Crate(game);
		crate[i]->init("crate"+IntToStr(i));		
	}
	crate[0]->getPhysicsEntity()->setPosition(hkVector4(-1.25,0.0f,20.75));
	crate[1]->getPhysicsEntity()->setPosition(hkVector4(-2   ,0.0f,20.75));
	crate[2]->getPhysicsEntity()->setPosition(hkVector4(-2,0.0f,20.75));
	crate[3]->getPhysicsEntity()->setPosition(hkVector4(-1,25,0.0f,20.0));
	crate[4]->getPhysicsEntity()->setPosition(hkVector4(-2   ,0.0f,20.0));
	crate[5]->getPhysicsEntity()->setPosition(hkVector4(-2.75,0.0f,20.0));
	crate[6]->getPhysicsEntity()->setPosition(hkVector4(-1,25,0.0f,20.75));
	crate[7]->getPhysicsEntity()->setPosition(hkVector4(-2   ,0.0f,20.75));
	crate[8]->getPhysicsEntity()->setPosition(hkVector4(-2.75,0.0f,20.75));

	crate[9]->getPhysicsEntity()->setPosition(hkVector4(-1.25,0.5f,20.75));
	crate[10]->getPhysicsEntity()->setPosition(hkVector4(-2   ,0.5f,20.75));
	crate[11]->getPhysicsEntity()->setPosition(hkVector4(-2.75,0.5f,20.75));
	crate[12]->getPhysicsEntity()->setPosition(hkVector4(-1,25,0.5f,20.0));
	crate[13]->getPhysicsEntity()->setPosition(hkVector4(-2   ,0.5f,20.0));
	crate[14]->getPhysicsEntity()->setPosition(hkVector4(-2.75,0.5f,20.0));
	crate[15]->getPhysicsEntity()->setPosition(hkVector4(-1,25,0.5f,20.750));
	crate[16]->getPhysicsEntity()->setPosition(hkVector4(-2   ,0.5f,20.750));
	crate[17]->getPhysicsEntity()->setPosition(hkVector4(-2.75,0.5f,20.750));

	crate[18]->getPhysicsEntity()->setPosition(hkVector4(-1.25,1.0f,20.75));
	crate[19]->getPhysicsEntity()->setPosition(hkVector4(-2   ,1.0f,20.75));
	crate[20]->getPhysicsEntity()->setPosition(hkVector4(-2.75,1.0f,20.75));
	crate[21]->getPhysicsEntity()->setPosition(hkVector4(-1,25,1.0f,20.0));
	crate[22]->getPhysicsEntity()->setPosition(hkVector4(-2   ,1.0f,20.0));
	crate[23]->getPhysicsEntity()->setPosition(hkVector4(-2.75,1.0f,20.0));
	crate[24]->getPhysicsEntity()->setPosition(hkVector4(-1,25,1.0f,20.75));
	crate[25]->getPhysicsEntity()->setPosition(hkVector4(-2   ,1.0f,20.75));
	crate[26]->getPhysicsEntity()->setPosition(hkVector4(-2.75,1.0f,20.75));

	crate[27]->getPhysicsEntity()->setPosition(hkVector4(-1.25,1.5f,-20.75));
	crate[28]->getPhysicsEntity()->setPosition(hkVector4(-20   ,1.5f,-20.75));
	crate[29]->getPhysicsEntity()->setPosition(hkVector4(-2.75,1.5f,-20.75));
	crate[30]->getPhysicsEntity()->setPosition(hkVector4(-1,25,1.5f,-20.0));
	crate[31]->getPhysicsEntity()->setPosition(hkVector4(-2   ,1.5f,-20.0));


	//RoadBarrier* barrier = new RoadBarrier(game);
	//barrier->init("barrier");
	//barrier->getPhysicsEntity()->setPosition(hkVector4(-5.5,0.25f,0.0f));

	Ogre::OverlayManager* overlayManager = Ogre::OverlayManager::getSingletonPtr();
	Ogre::Overlay* overlay = overlayManager->getByName("debugText");
	overlay->show();
	debugTextOverlay  = (Ogre::TextAreaOverlayElement*)overlayManager->getOverlayElement("debugTextArea");
	debugTextOverlay->show();

	updateCamera();

	game->visualSystem.unlockThread();

	return true;
}

//————————————————————————————————————————————————————————————————————————————————————————

void GameVisualScene::update()
{
	VisualScene::update();
	UpdateListenerMgr::getInstance()->update(EV_UPDATE_VISUAL_ENTITIES,0);

	updateCamera();
	updateOverlays();
}

//————————————————————————————————————————————————————————————————————————————————————————

void GameVisualScene::updateCamera()
{
	static f32 rotz;
	static f32 rotx = 5.0;
	static f32 roty = 5.0;

	rotz += f32(game->inputSystem.getMouseMovement(2))/200.0f; 
	//rotz  = clampValue(rotz,1.0f,50.0f);
	rotz  = clampValue(rotz,5.0f,25.0f);

	if(game->inputSystem.mouse.state.isBtnDown(1)) 
	{
		rotx += (f32)game->inputSystem.getMouseMovement(0);
		roty += (f32)game->inputSystem.getMouseMovement(1);

		rotx = circularValue(rotx,0.0f,360.0f);
		roty = clampValue(roty,5.0f,85.0f); 

		Ogre::Vector3 pos = Ogre::Vector3::ZERO;
		pos.z = rotz*cos(hmath::deg(rotx).asRad())*sin(hmath::deg(roty).asRad());
		pos.x = rotz*sin(hmath::deg(rotx).asRad())*sin(hmath::deg(roty).asRad());
		pos.y = rotz*cos(hmath::deg(roty).asRad());

		game->visualSystem.getCamera()->setPosition(pos - Ogre::Vector3(2.5f,1.5f,0.0f));
		game->inputSystem.resetMouseMovement();
	}	
}

//————————————————————————————————————————————————————————————————————————————————————————

void GameVisualScene::updateOverlays()
{
	str text = StrPrintf("visual frame #%d maxFPS = %.2f\n",game->visualSystem.getCurrentFrameNum(),game->visualSystem.getMaxFPS());
	text    += StrPrintf("physics last step %dms\n",game->physicsSystem.getLastTimeElapsed());
	text    += DebugRegistry::getInstance()->print();
	debugTextOverlay->setCaption(text);
}

//————————————————————————————————————————————————————————————————————————————————————————

void GameVisualScene::cleanUp()
{
	VisualScene::cleanUp();
}

