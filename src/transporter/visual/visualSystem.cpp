#include "transporter/visual/visualSystem.h"

VisualSystem::VisualSystem()
{
	visualRoot		= NULL;
	renderWindow    = NULL;
	renderSystem    = NULL;
	renderCamera    = NULL;
	renderViewport  = NULL;
	sceneMgr		= NULL;
	isVisualInited  = false;
	isVisualRunning = false;
}

//————————————————————————————————————————————————————————————————————————————————————————

void VisualSystem::init()
{
	visualRoot = new Ogre::Root("visual-plugins.cfg",
		                        "visual-config.cfg",
								"visual-log.txt");

	glPlugin = new Ogre::GLPlugin;
	visualRoot->installPlugin(glPlugin);

	octreePlugin = new Ogre::OctreePlugin;
	visualRoot->installPlugin(octreePlugin);

	cgPlugin = new Ogre::CgPlugin;
	visualRoot->installPlugin(cgPlugin);

	renderSystem = visualRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
	visualRoot->setRenderSystem(renderSystem);

	renderSystem->setConfigOption("Full Screen", "No");
	renderSystem->setConfigOption("Video Mode", "800 x 600 @ 32-bit");
	renderSystem->setConfigOption("VSync", "No");
	renderSystem->setConfigOption("RTT Preferred Mode","FBO");	
	renderSystem->setConfigOption("FSAA","4");

	Ogre::ConfigFile cf;
	cf.load("visual-resources.cfg");
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	str secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}

	renderWindow   = visualRoot->initialise(true);
	//Ogre::NameValuePairList misc;
	//misc["externalWindowHandle"] = Ogre::StringConverter::toString((int)window->getHandle());
	//renderWindow = visualRoot->createRenderWindow("Main RenderWindow", 800, 600, false, &misc);
	renderWindow->getCustomAttribute("WINDOW", &renderWindowHandle);

	sceneMgr = visualRoot->createSceneManager(Ogre::ST_EXTERIOR_CLOSE);

	renderCamera = sceneMgr->createCamera("mainCamera");
	renderCamera->setNearClipDistance( 1 );
	renderCamera->setFarClipDistance(99999);

	renderViewport = renderWindow->addViewport(renderCamera);
	renderViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
	renderCamera->setAspectRatio(f32(renderViewport->getActualWidth()) / 
		                         f32(renderViewport->getActualHeight()));

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	if( renderWindow &&
		renderSystem &&
		renderCamera &&
		renderViewport &&
		sceneMgr &&
		visualRoot )
	{
		isVisualInited = true;
		createScene();
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

VisualSystem::~VisualSystem()
{
	cleanUp();
}

//————————————————————————————————————————————————————————————————————————————————————————

void VisualSystem::run()
{
	if(!isVisualInited)
	{
		init();
	}

	isVisualRunning    = true;
	u64 usedtick       = 0;
	u32 currentFrame   = 0;
	u32 framePerSecond = 60;

	LARGE_INTEGER starttick;
	LARGE_INTEGER tick;
	LARGE_INTEGER tickPerSecond;

	QueryPerformanceFrequency(&tickPerSecond);
	QueryPerformanceCounter(&tick);
	while( !renderWindow->isClosed() && isVisualRunning)
	{
		QueryPerformanceCounter(&starttick);

		Ogre::WindowEventUtilities::messagePump();
		updateScene();
		visualRoot->renderOneFrame();

		currentFrame++;
		u64 lasttick = tick.QuadPart;
		u32 frameleft = framePerSecond - currentFrame;
		QueryPerformanceCounter(&tick);

		if( ((usedtick+(tick.QuadPart - lasttick)) < (u64)tickPerSecond.QuadPart) && frameleft)
		{			
			u64 deltatick = tick.QuadPart - starttick.QuadPart;
			usedtick     += tick.QuadPart - lasttick;
			u64 tickleft  = tickPerSecond.QuadPart - usedtick;
			u64 sleeptick = tickleft/frameleft;
			u32 sleepMS   = (u32)(1000*sleeptick/tickPerSecond.QuadPart);	

			Sleep(sleepMS);
		}
		else
		{
			usedtick = 0;
			currentFrame = 0;
			frameleft = framePerSecond;
		}
	}

	cleanUp();
}

//————————————————————————————————————————————————————————————————————————————————————————

void VisualSystem::stop()
{
	isVisualRunning = false;
}

//————————————————————————————————————————————————————————————————————————————————————————

bit VisualSystem::isRunnning()
{
	return isVisualRunning;
}

//————————————————————————————————————————————————————————————————————————————————————————

void VisualSystem::updateScene()
{

}

//————————————————————————————————————————————————————————————————————————————————————————

void VisualSystem::createScene()
{
	sceneMgr->setAmbientLight(Ogre::ColourValue(1.0,1.0,1.0));

	Ogre::Light* spotLight = sceneMgr->createLight("SpotLight");
	spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
	spotLight->setPosition(0,100,0);
	spotLight->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);
	spotLight->setSpecularColour(0.9,0.9,1.0);	
	spotLight->setCastShadows(true);

	sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
	sceneMgr->setShadowColour( Ogre::ColourValue(0.5, 0.5, 0.5) );
	sceneMgr->setSkyBox(true,"skybox",10000);

	Ogre::Plane surfacePlane;
	surfacePlane.normal = Ogre::Vector3::UNIT_Y;
	surfacePlane.d = 0;
	Ogre::MeshManager::getSingleton().createPlane("surface",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		surfacePlane,
		4096, 4096, 128, 128, true, 1, 128, 128, Ogre::Vector3::UNIT_Z);

	Ogre::SceneNode* surfaceNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* surfaceEntity = sceneMgr->createEntity( "surface", "surface" );
	surfaceEntity->setMaterialName("asphalt");
	surfaceNode->attachObject(surfaceEntity);
	surfaceNode->setPosition(0,0,0);

	renderCamera->setPosition(0,20,-300);
	renderCamera->lookAt(0,0,1);
}

//————————————————————————————————————————————————————————————————————————————————————————

void VisualSystem::cleanUp()
{
	stop();

	if(visualRoot)
	{
		delete visualRoot;
		visualRoot = NULL;
		renderWindow = NULL;
		renderCamera = NULL;
		renderViewport = NULL;
		renderSystem = NULL;
	}

	//delete sceneMgr;
	//sceneMgr = NULL;

	if(glPlugin)
	{
		delete glPlugin;
		glPlugin = NULL;
	}

	isVisualInited = false;
}