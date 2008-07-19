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
	light->setPosition(800,500,-100);
	Ogre::Vector3 dir = -light->getPosition();
	dir.normalise();
	light->setDirection(dir);
	light->setSpecularColour(1.0f,1.0f,1.0f);
	light->setDiffuseColour(0.85f,0.85f,0.865f);
	//light->setSpotlightRange(Ogre::Degree(50), Ogre::Degree(75));
	light->setPowerScale(1.0f);
	light->setCastShadows(true);	

	//Ogre::LiSPSMShadowCameraSetup* cameraSetup = new Ogre::LiSPSMShadowCameraSetup;
	//game->visualSystem.getSceneMgr()->setShadowCameraSetup(Ogre::ShadowCameraSetupPtr(cameraSetup));

	game->visualSystem.getSceneMgr()->getRootSceneNode()->attachObject(light);

	game->visualSystem.getSceneMgr()->setAmbientLight(Ogre::ColourValue(0.95,0.85,0.65));
	//game->visualSystem.getSceneMgr()->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE);
	game->visualSystem.getSceneMgr()->setShadowTextureSize(1024);
	//game->visualSystem.getSceneMgr()->setShadowTextureSettings(1024,2);
	game->visualSystem.getSceneMgr()->setShadowFarDistance(10);
	game->visualSystem.getSceneMgr()->setShadowDirLightTextureOffset(0.15);
	game->visualSystem.getSceneMgr()->setShadowTextureSelfShadow(true);
	game->visualSystem.getSceneMgr()->setShadowColour( Ogre::ColourValue(0.35f, 0.35f, 0.35f) );
	game->visualSystem.getSceneMgr()->setSkyBox(true,"skybox",1000);	
	game->visualSystem.getSceneMgr()->setShadowTextureCasterMaterial("depthShadowMapCasterMaterial");
	//game->visualSystem.getSceneMgr()->setShadowTextureCasterMaterial("VarianceShadowMapping/ShadowCaster");
	game->visualSystem.getSceneMgr()->setShadowTexturePixelFormat(PF_FLOAT32_R);
	game->visualSystem.getSceneMgr()->setShadowCasterRenderBackFaces(true);
	game->visualSystem.getSceneMgr()->setShadowTechnique(SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED);


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
	rotz  = clampValue(rotz,5.0f,15.0f);

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

		game->visualSystem.getCamera()->setPosition(pos - Ogre::Vector3(0.0f,4.0f,6.0f));
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