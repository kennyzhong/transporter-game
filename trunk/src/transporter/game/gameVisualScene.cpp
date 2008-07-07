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
	light->setType(Ogre::Light::LT_SPOTLIGHT);
	light->setPosition(600,1500,800);
	Ogre::Vector3 dir = -light->getPosition();
	dir.normalise();
	light->setDirection(dir);
	light->setSpecularColour(1.0f,1.0f,1.0f);
	light->setDiffuseColour(0.85f,0.85f,0.865f);
	light->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(60));
	light->setPowerScale(1.0f);
	light->setCastShadows(true);	

	game->visualSystem.getSceneMgr()->getRootSceneNode()->attachObject(light);

	game->visualSystem.getSceneMgr()->setAmbientLight(Ogre::ColourValue(0.0,0.0,0.0));
	game->visualSystem.getSceneMgr()->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	game->visualSystem.getSceneMgr()->setShadowTextureSize(512);
	game->visualSystem.getSceneMgr()->setShadowFarDistance(64);
	game->visualSystem.getSceneMgr()->setShadowTextureSelfShadow(true);
	game->visualSystem.getSceneMgr()->setShadowColour( Ogre::ColourValue(0.35f, 0.35f, 0.35f) );
	game->visualSystem.getSceneMgr()->setSkyBox(true,"skybox",3000);	

	Ogre::OverlayManager* overlayManager = Ogre::OverlayManager::getSingletonPtr();
	Ogre::Overlay* overlay = overlayManager->getByName("debugText");
	overlay->show();
	debugTextOverlay  = (Ogre::TextAreaOverlayElement*)overlayManager->getOverlayElement("debugTextArea");
	debugTextOverlay->show();

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
	static f32 rotx;
	static f32 roty;

	rotz += f32(game->inputSystem.getMouseMovement(2))/10.0f; 
	//rotz  = clampValue(rotz,1.0f,50.0f);
	rotz  = clampValue(rotz,5.0f,50.0f);

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