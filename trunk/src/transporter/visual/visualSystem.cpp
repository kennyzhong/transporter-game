#include "transporter.h"

VisualSystem::VisualSystem()
{
	visualRoot		= NULL;
	renderSystem    = NULL;
	sceneMgr		= NULL;
	scene           = NULL;
	game            = NULL;
	primaryRenderWindow = NULL;
	visualThreadSignal  = NULL;
	visualInitSignal    = NULL;
	visualThread    = NULL;
	isVisualBooted  = false;
	isVisualInited  = false;
	isVisualRunning = false;	
}

//————————————————————————————————————————————————————————————————————————————————————————

VisualSystem::~VisualSystem()
{
	stop();
}

//————————————————————————————————————————————————————————————————————————————————————————

void VisualSystem::cleanUp()
{	
	//if(visualRoot)
	//{
	//	delete visualRoot;
	//}

	for(u32 i=0 ; i<plugins.size() ; i++)
	{
		delete plugins.at(i);
	}
	plugins.clear();
	renderCameras.clear();
	renderWindows.clear();
	renderViewports.clear();
	scenes.clear();

	isVisualInited  = false;
	isVisualRunning = false;

	primaryRenderWindow = NULL;
	visualRoot          = NULL;
	renderSystem        = NULL;
	sceneMgr            = NULL;
}

//————————————————————————————————————————————————————————————————————————————————————————

bit VisualSystem::init(Game* game)
{
	if(!isVisualInited)
	{
		if(visualThreadSignal)
		{
			CloseHandle(visualThreadSignal);
			visualThreadSignal = NULL;
		}
		if(visualInitSignal)
		{
			CloseHandle(visualInitSignal);
			visualInitSignal = NULL;
		}
		visualThreadSignal	= CreateEvent(NULL,TRUE,FALSE,NULL);
		visualInitSignal    = CreateEvent(NULL,TRUE,FALSE,NULL);
		if(visualThreadSignal && visualInitSignal)
		{
			this->game = game;	
			this->isVisualRunning = true;
			visualThread = CreateThread(NULL,4*1024*1024,visualThreadProc,this,0,NULL);
			if(visualThread)
			{
				WaitForSingleObject(visualInitSignal,INFINITE);
			}
		}
	}
	return this->isVisualInited;
}

//————————————————————————————————————————————————————————————————————————————————————————

void VisualSystem::run()
{
	if(isVisualInited)
	{
		SetEvent(visualThreadSignal);
	}	
}

//————————————————————————————————————————————————————————————————————————————————————————

void VisualSystem::stop()
{
	isVisualRunning = false;
	SetEvent(visualThreadSignal);
	if(WaitForSingleObject(visualThread,5000) == WAIT_TIMEOUT)
	{
		TerminateThread(visualThread,1);
	}
	ResetEvent(visualInitSignal);
	ResetEvent(visualThreadSignal);
}

//————————————————————————————————————————————————————————————————————————————————————————

bit VisualSystem::isRunnning()
{
	return isVisualRunning;
}

//————————————————————————————————————————————————————————————————————————————————————————

HWND VisualSystem::getWindowHandle(Ogre::RenderWindow* window)
{
	HWND result = NULL;
	window->getCustomAttribute("WINDOW", &result);	
	return result;
}

//————————————————————————————————————————————————————————————————————————————————————————

Ogre::RenderWindow* VisualSystem::getPrimaryRenderWindow()
{
	return primaryRenderWindow;
}

//————————————————————————————————————————————————————————————————————————————————————————

Ogre::RenderWindow* VisualSystem::getRenderWindow(str name)
{
	std::map<str,Ogre::RenderWindow*>::iterator it = renderWindows.find(name);
	if(it!=renderWindows.end())
	{
		return it->second;
	}
	return NULL;
}

//————————————————————————————————————————————————————————————————————————————————————————

Ogre::RenderSystem* VisualSystem::getRenderSystem()
{
	return renderSystem;
}

//————————————————————————————————————————————————————————————————————————————————————————

Ogre::Camera* VisualSystem::getCamera(u32 index)
{
	if(index < renderCameras.size())
	{
		return renderCameras.at(index);
	}
	return NULL;
}

//————————————————————————————————————————————————————————————————————————————————————————

Ogre::Camera* VisualSystem::getCamera(str name)
{
	for(u32 i=0 ; i<renderCameras.size() ; i++)
	{
		if(renderCameras.at(i)->getName() == name)
		{
			return renderCameras.at(i);
		}
	}
	return NULL;
}

//————————————————————————————————————————————————————————————————————————————————————————

Ogre::SceneManager* VisualSystem::getSceneMgr()
{
	return sceneMgr;
}

//————————————————————————————————————————————————————————————————————————————————————————

u32 VisualSystem::getCurrentFrameNum()
{
	return currentFrame;
}

//————————————————————————————————————————————————————————————————————————————————————————

bit VisualSystem::createVisualRoot()
{	
	str visualConfigFile = "visual-config.cfg";
	str pluginConfigFile = "visual-plugins.cfg";
	str loggingFile		 = "visual-log.txt";

	XSSNode* visualCfgNode = ConfigMgr::get("game.config");
	if(visualCfgNode)
	{
		XSSNode* cfgNode = visualCfgNode->get("GameConfig.visualConfigFile");
		if(cfgNode)
		{
			visualConfigFile = cfgNode->getValue();
		}

		cfgNode = visualCfgNode->get("GameConfig.pluginConfigFile");
		if(cfgNode)
		{
			pluginConfigFile = cfgNode->getValue();
		}

		cfgNode = visualCfgNode->get("GameConfig.loggingFile");
		if(cfgNode)
		{
			loggingFile = cfgNode->getValue();
		}
	}	
	visualRoot = new Ogre::Root(pluginConfigFile,visualConfigFile,loggingFile);
	Ogre::LogManager::getSingletonPtr()->getDefaultLog()->addListener(&logListener);
	return visualRoot!=NULL;
}

//————————————————————————————————————————————————————————————————————————————————————————

bit VisualSystem::createRenderSystem()
{
	if(!visualRoot)
	{
		return false;
	}

	str renderSystemName = "Direct3D9 Rendering Subsystem";
	std::map<str,str> renderSystemConfigKey;

	XSSNode* visualCfgNode = ConfigMgr::get("game.config");
	if(visualCfgNode)
	{
		XSSNode* cfgNode = visualCfgNode->get("GameConfig.useRenderSystem");
		XSSNode* renderSystemCfgNode = NULL;
		if(cfgNode)
		{
			renderSystemName = cfgNode->getValue();
			cfgNode = visualCfgNode->get("GameConfig");
			if(cfgNode)
			{
				for(u32 i=0 ; i<cfgNode->countChild() ; i++)
				{
					XSSNode* childNode = cfgNode->getChild(i);
					if( childNode->getKey() == "renderSystem" &&
						childNode->getNdx() == renderSystemName )
					{
						renderSystemCfgNode = childNode;
						break;
					}
				}
			}
		}
		if(renderSystemCfgNode)
		{
			for(u32 i=0 ; i<renderSystemCfgNode->countChild() ; i++)
			{
				XSSNode* childNode = renderSystemCfgNode->getChild(i);
				if(childNode->getKey() == "config" || childNode->getKey() == "fullscreenOptions.config")
				{
					str cfgKey = childNode->getNdx();
					str cfgValue = childNode->getValue();
					if(cfgKey.length()>0 && cfgValue.length()>0)
					{
						renderSystemConfigKey[cfgKey] = cfgValue;
					}
				}
			}
		}
	}

	if(renderSystemName == "Direct3D9 Rendering Subsystem")
	{
		Ogre::D3D9Plugin* dxPlugin = new Ogre::D3D9Plugin;
		visualRoot->installPlugin(dxPlugin);
		plugins.push_back(dxPlugin);
	}
	else if(renderSystemName == "OpenGL Rendering Subsystem")
	{
		Ogre::GLPlugin* glPlugin = new Ogre::GLPlugin;
		visualRoot->installPlugin(glPlugin);
		plugins.push_back(glPlugin);
	}

	renderSystem = visualRoot->getRenderSystemByName(renderSystemName);
	if(renderSystem)
	{		
		std::map<str,str>::iterator it = renderSystemConfigKey.begin();
		for(it ; it!=renderSystemConfigKey.end() ; it++)
		{
			renderSystem->setConfigOption(it->first,it->second);
		}
		visualRoot->setRenderSystem(renderSystem);	
		visualRoot->initialise(false);
		return true;
	}
	return false;
}

//————————————————————————————————————————————————————————————————————————————————————————

bit VisualSystem::createInternalPlugins()
{
	if(!visualRoot)
	{
		return false;
	}

	bit installOctreeSceneMgr = true;
	bit installCgManager = true;
	XSSNode* visualCfgNode = ConfigMgr::get("game.config");
	if(visualCfgNode)
	{
		XSSNode* node = visualCfgNode->get("GameConfig.internalPlugins.OctreeSceneMgr");
		if(node)
		{
			installOctreeSceneMgr = node->getValueAsBool();
		}

		node = visualCfgNode->get("GameConfig.internalPlugins.nVidiaCG");
		if(node)
		{
			installCgManager = node->getValueAsBool();
		}
	}

	if(installOctreeSceneMgr)
	{
		Ogre::OctreePlugin* octreePlugin = new Ogre::OctreePlugin;
		visualRoot->installPlugin(octreePlugin);
		plugins.push_back(octreePlugin);
	}

	if(installCgManager)
	{
		Ogre::CgPlugin* cgPlugin = new Ogre::CgPlugin;
		visualRoot->installPlugin(cgPlugin);
		plugins.push_back(cgPlugin);
	}

	return true;
}

//————————————————————————————————————————————————————————————————————————————————————————

bit VisualSystem::createRenderCamera()
{
	if(!visualRoot || !sceneMgr)
	{
		return false;
	}
	bit result = false;

	XSSNode* visualCfgNode = ConfigMgr::get("game.config");
	if(visualCfgNode)
	{
		XSSNode* rootNode = visualCfgNode->get("GameConfig");
		for(u32 i=0 ; i<rootNode->countChild() ; i++)
		{
			XSSNode* childNode = rootNode->getChild(i);
			if(childNode->getKey() == "camera")
			{
				str cameraName = childNode->getNdx();
				if(cameraName.empty())
				{
					cameraName = "defaultCamera";
				}
				Ogre::Camera* camera = sceneMgr->createCamera(cameraName);
				result |= (camera!=NULL);
				if(camera)
				{
					renderCameras.push_back(camera);
					camera->setNearClipDistance( 1.0f );
					camera->setFarClipDistance(1000.0f);
					camera->setAspectRatio(4.0f/3.0f);

					XSSNode* cfgNode = childNode->get("nearClipDistance");
					if(cfgNode)
					{
						camera->setNearClipDistance(cfgNode->getValueAsFloat());
					}

					cfgNode = childNode->get("farClipDistance");
					if(cfgNode)
					{
						camera->setFarClipDistance(cfgNode->getValueAsFloat());
					}

					cfgNode = childNode->get("aspectRatio");
					if(cfgNode)
					{
						if(cfgNode->getValue() == "videoMode default")
						{
							if(renderSystem)
							{
								Ogre::ConfigOptionMap::iterator it = renderSystem->getConfigOptions().find("Video Mode");
								if(it != renderSystem->getConfigOptions().end())
								{
									str optionValue = it->second.currentValue;

									str::size_type widthEnd  = optionValue.find(' ');
									str::size_type heightEnd = optionValue.find(' ', widthEnd+3);
									u32 width  = StrToInt(optionValue.substr(0, widthEnd));
									u32 height = StrToInt(optionValue.substr(widthEnd+3, heightEnd));

									if(height != 0)
									{
										camera->setAspectRatio((f32)width/(f32)height);
									}
								}
							}
						}
					}
				}				
			}
		}
	}

	if(!result)
	{
		Ogre::Camera* camera = sceneMgr->createCamera("defaultCamera");
		renderCameras.push_back(camera);
		camera->setNearClipDistance( 1.0f );
		camera->setFarClipDistance(1000.0f);
		camera->setAspectRatio(4.0f/3.0f);
		return true;
	}
	return result;
}

//————————————————————————————————————————————————————————————————————————————————————————

bit VisualSystem::createSceneMgr()
{
	if(!visualRoot)
	{
		return false;
	}

	XSSNode* visualCfgNode = ConfigMgr::get("game.config");
	if(visualCfgNode)
	{
		XSSNode* sceneMgrCfgNode = visualCfgNode->get("GameConfig.sceneManager");
		if(sceneMgrCfgNode)
		{
			bit selectByMask = true;
			str instanceName = Ogre::StringUtil::BLANK;
			Ogre::SceneTypeMask sceneMask = Ogre::ST_GENERIC;

			XSSNode* cfgNode = sceneMgrCfgNode->get("instanceName");
			if(cfgNode)
			{
				instanceName = cfgNode->getValue();
				if(instanceName == "default")
				{
					instanceName = Ogre::StringUtil::BLANK;
				}
			}

			cfgNode = sceneMgrCfgNode->get("selectByMask");
			if(cfgNode)
			{
				selectByMask = cfgNode->getValueAsBool();
			}

			if(selectByMask)
			{
				cfgNode = sceneMgrCfgNode->get("selectionMask");
				if(cfgNode)
				{
					sceneMask = (Ogre::SceneTypeMask)cfgNode->getValueAsInt();
					sceneMgr = visualRoot->createSceneManager(sceneMask,instanceName);
					return sceneMgr!=NULL;
				}
			}
			else
			{
				str sceneMgrName = "";
				cfgNode = sceneMgrCfgNode->get("typeName");
				if(cfgNode)
				{
					sceneMgrName = cfgNode->getValue();
					sceneMgr = visualRoot->createSceneManager(sceneMgrName,instanceName);
					return sceneMgr!=NULL;
				}
			}
		}
	}
	else
	{
		sceneMgr = visualRoot->createSceneManager(Ogre::ST_GENERIC);
	}
	return true;
}

//————————————————————————————————————————————————————————————————————————————————————————

bit VisualSystem::createRenderWindow()
{
	if(!visualRoot)
	{
		return false;
	}

	bit result = false;
	u32 defaultWidth = 800;
	u32 defaultHeight = 600;
	bit defaultFullscreen = false;
	str defaultTitle = "RenderWindow";

	if(renderSystem)
	{
		Ogre::ConfigOptionMap::iterator it = renderSystem->getConfigOptions().find("Video Mode");
		if(it != renderSystem->getConfigOptions().end())
		{
			str optionValue = it->second.currentValue;

			str::size_type widthEnd  = optionValue.find(' ');
			str::size_type heightEnd = optionValue.find(' ', widthEnd+3);
			defaultWidth  = StrToInt(optionValue.substr(0, widthEnd));
			defaultHeight = StrToInt(optionValue.substr(widthEnd+3, heightEnd));
		}
		it = renderSystem->getConfigOptions().find("Full Screen");
		if(it != renderSystem->getConfigOptions().end())
		{
			if(it->second.currentValue == "No")
			{
				defaultFullscreen = false;
			}
			else
			{
				defaultFullscreen = true;
			}
		}
	}

	XSSNode* visualCfgNode = ConfigMgr::get("game.config");
	if(visualCfgNode)
	{
		XSSNode* rootNode = visualCfgNode->get("GameConfig");
		if(rootNode)
		{
			for(u32 i=0 ; i<rootNode->countChild() ; i++)
			{
				XSSNode* childNode = rootNode->getChild(i);
				if(childNode->getKey() == "window")
				{
					str windowName = childNode->getNdx();
					str windowTitle = defaultTitle;
					i32 width  = defaultWidth;
					i32 height = defaultHeight;
					bit fullscreen = defaultFullscreen;
					Ogre::NameValuePairList wndParams;

					if(windowName.empty())
					{
						windowName = defaultTitle+IntToStr(i);
					}

					XSSNode* cfgNode = childNode->get("width");
					if(cfgNode)
					{
						if(cfgNode->getValue() != "default")
						{
							width = cfgNode->getValueAsInt();
							if(width <= 0)
							{
								width = defaultWidth;
							}							
						}					
					}

					cfgNode = childNode->get("height");
					if(cfgNode)
					{
						if(cfgNode->getValue() != "default")
						{
							height = cfgNode->getValueAsInt();
							if(height <= 0)
							{
								height = defaultHeight;
							}							
						}					
					}

					cfgNode = childNode->get("fullScreen");
					if(cfgNode)
					{
						fullscreen = cfgNode->getValueAsBool();
					}

					cfgNode = childNode->get("title");
					if(cfgNode)
					{
						windowTitle = cfgNode->getValue();
						if(windowTitle.empty())
						{
							windowTitle = defaultTitle;
						}
					}		

					cfgNode = childNode->get("FSAA");
					if(cfgNode)
					{
						wndParams["FSAA"] = cfgNode->getValue();
					}		

					cfgNode = childNode->get("FSAAQuality");
					if(cfgNode)
					{
						wndParams["FSAAQuality"] = cfgNode->getValue();
					}

					cfgNode = childNode->get("border");
					if(cfgNode)
					{
						wndParams["border"] = cfgNode->getValue();
					}

					cfgNode = childNode->get("depthBuffer");
					if(cfgNode)
					{
						wndParams["depthBuffer"] = cfgNode->getValue();
					}

					cfgNode = childNode->get("outerDimensions");
					if(cfgNode)
					{
						wndParams["outerDimensions"] = cfgNode->getValue();
					}

					cfgNode = childNode->get("colourDepth");
					if(cfgNode)
					{
						str bitdepth = cfgNode->getValue();
						if(bitdepth == "default")
						{
							Ogre::ConfigOptionMap::iterator it = getRenderSystem()->getConfigOptions().find("colourDepth");
							if(it != getRenderSystem()->getConfigOptions().end())
							{
								bitdepth = it->second.currentValue;
							}
						}						
					}
					if(fullscreen)
					{
						str displayFreq = "60";
						cfgNode = childNode->get("displayFrequency");
						if(cfgNode)
						{
							wndParams["displayFrequency"] = cfgNode->getValue();
						}

						str vsync = "false";
						Ogre::ConfigOptionMap::iterator it = getRenderSystem()->getConfigOptions().find("VSync");
						if(it != getRenderSystem()->getConfigOptions().end())
						{
							vsync = it->second.currentValue;
						}
						wndParams["vsync"] = vsync;
					}

					wndParams["width"] = IntToStr(width);
					wndParams["height"] = IntToStr(height);
					wndParams["title"] = windowTitle;

					Ogre::RenderWindow* renderWindow = visualRoot->createRenderWindow(windowTitle,width,height,fullscreen,&wndParams);
					if(renderWindow)
					{						
						cfgNode = childNode->get("primary");
						if(cfgNode)
						{
							if(cfgNode->getValueAsBool())
							{
								this->primaryRenderWindow = renderWindow;
							}
						}
						renderWindows[windowName] = renderWindow;	
						result |= true;
					}				
				}			
			}
		}
		result |= false;
	}

	if(!result)
	{
		Ogre::RenderWindow* renderWindow = visualRoot->createRenderWindow(defaultTitle,
																		  defaultWidth,
																		  defaultHeight,
																		  defaultFullscreen);
		renderWindows["primaryRenderWindow"] = renderWindow;
		primaryRenderWindow = renderWindow;
		return renderWindow!=NULL;
	}
	return result;
}

//————————————————————————————————————————————————————————————————————————————————————————

bit VisualSystem::createRenderViewport()
{
	bit result = false;
	XSSNode* visualCfgNode = ConfigMgr::get("game.config");
	if(visualCfgNode)
	{
		XSSNode* rootNode = visualCfgNode->get("GameConfig");
		for(u32 k=0 ; k<rootNode->countChild() ; k++)
		{
			XSSNode* vpNode = rootNode->getChild(k);
			if(vpNode->getKey() == "viewport")
			{
				Ogre::Camera* camera = getCamera();
				Ogre::RenderWindow* window = getPrimaryRenderWindow();
				XSSNode* cfgNode = vpNode->get("camera");
				if(cfgNode)
				{
					str cameraName = cfgNode->getValue();
					if(cameraName.empty())
					{
						cameraName = camera->getName();
					}
					else
					{
						camera = getCamera(cameraName);
						if(!camera)
						{
							camera = getCamera();
							cameraName = camera->getName();
						}
					}
				}

				f32 vpPosLeft = 0.0f;
				f32 vpPosTop  = 0.0f;
				f32 vpWidth   = 1.0f;
				f32 vpHeight  = 1.0f;
				u32 vpZOrder  = k;

				cfgNode = vpNode->get("windowOffsets.left");
				if(cfgNode)
				{
					vpPosLeft = cfgNode->getValueAsFloat();
				}

				cfgNode = vpNode->get("windowOffsets.top");
				if(cfgNode)
				{
					vpPosTop = cfgNode->getValueAsFloat();
				}

				cfgNode = vpNode->get("windowOffsets.width");
				if(cfgNode)
				{
					vpWidth = cfgNode->getValueAsFloat();
				}

				cfgNode = vpNode->get("windowOffsets.height");
				if(cfgNode)
				{
					vpHeight = cfgNode->getValueAsFloat();
				}

				cfgNode = vpNode->get("windowOffsets.zOrder");
				if(cfgNode)
				{
					vpZOrder = cfgNode->getValueAsInt();
				}

				cfgNode = vpNode->get("renderWindow");
				if(cfgNode)
				{
					str windowName = cfgNode->getValue();
					if(windowName.empty())
					{
						windowName = window->getName();
					}
					else
					{
						window = getRenderWindow(windowName);
						if(!window)
						{
							window = getPrimaryRenderWindow();
							windowName = window->getName();
						}
					}
				}

				Ogre::Viewport* renderViewport = window->addViewport(camera,vpZOrder,vpPosLeft,vpPosTop,vpWidth,vpHeight);				
				result |= (renderViewport!=NULL);

				if(renderViewport)
				{
					renderViewports.push_back(renderViewport);

					bit enableOverlay    = true;
					bit enableShadows    = true;
					bit enableSkies      = true;
					bit clearDepthBuffer = true;
					bit clearColorBuffer = true;
					bit clearStencilBuffer = false;

					cfgNode = vpNode->get("enableOverlay");
					if(cfgNode)
					{
						enableOverlay = cfgNode->getValueAsBool();
					}

					cfgNode = vpNode->get("enableShadows");
					if(cfgNode)
					{
						enableShadows = cfgNode->getValueAsBool();
					}

					cfgNode = vpNode->get("enableSkies");
					if(cfgNode)
					{
						enableSkies = cfgNode->getValueAsBool();
					}

					cfgNode = vpNode->get("clearDepthBufferEveryFrame");
					if(cfgNode)
					{
						clearDepthBuffer = cfgNode->getValueAsBool();
					}

					cfgNode = vpNode->get("clearColorBufferEveryFrame");
					if(cfgNode)
					{
						clearColorBuffer = cfgNode->getValueAsBool();
					}

					cfgNode = vpNode->get("clearStencilBufferEveryFrame");
					if(cfgNode)
					{
						clearStencilBuffer = cfgNode->getValueAsBool();
					}

					renderViewport->setOverlaysEnabled(enableOverlay);
					renderViewport->setShadowsEnabled(enableShadows);
					renderViewport->setSkiesEnabled(enableSkies);

					bit clearBuffer = clearColorBuffer | clearDepthBuffer | clearStencilBuffer;
					u32 clearFlag = 0;
					if(clearColorBuffer)
					{
						clearFlag |= Ogre::FBT_COLOUR;
					}
					if(clearDepthBuffer)
					{
						clearFlag |= Ogre::FBT_DEPTH;
					}
					if(clearStencilBuffer)
					{
						clearFlag |= Ogre::FBT_STENCIL;
					}

					renderViewport->setClearEveryFrame(clearBuffer,clearFlag);
				}				
			}
		}
	}
	
	if(!result)
	{
		Ogre::RenderWindow* renderWindow = getPrimaryRenderWindow();
		if(renderWindow)
		{
			Ogre::Viewport* renderViewport = renderWindow->addViewport(renderCameras.at(0));
			renderViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
			renderViewport->setOverlaysEnabled(true);
			renderViewports.push_back(renderViewport);
			return true;
		}
		return false;
	}	
	return result;
}

//————————————————————————————————————————————————————————————————————————————————————————

bit VisualSystem::loadResources(str resourceGroupName)
{
	if(!visualRoot)
	{
		return false;
	}

	XSSNode* visualCfgNode = ConfigMgr::get("game.config");
	if(visualCfgNode)
	{
		XSSNode* rootNode = visualCfgNode->get("GameConfig");
		if(rootNode)
		{
			for(u32 i=0 ; i<rootNode->countChild() ; i++)
			{
				XSSNode* childNode = rootNode->getChild(i);
				if( childNode->getKey() == "resourceGroup")
				{
					str resourceGrpName = childNode->getNdx();
					if(resourceGrpName == resourceGroupName)
					{
						EnterCriticalSection(&lock);	
						Ogre::ResourceGroupManager* srcGroupMgr = Ogre::ResourceGroupManager::getSingletonPtr();
						for(u32 k=0 ; k<childNode->countChild() ; k++)
						{
							XSSNode* foldersNode = childNode->getChild(k);
							if(foldersNode)
							{
								str path = foldersNode->getValue();
								srcGroupMgr->addResourceLocation(path,foldersNode->getKey(),resourceGrpName);
							}
						}		
						srcGroupMgr->initialiseResourceGroup(resourceGrpName);	
						LeaveCriticalSection(&lock);
					}		
				}
			}
		}		
	}
	return true;
}

//————————————————————————————————————————————————————————————————————————————————————————

void VisualSystem::addScene( VisualScene* scene )
{
	if(isVisualInited)
	{
		EnterCriticalSection(&lock);
		for(u32 i=0 ; i<scenes.size() ; i++)
		{
			if(scenes.at(i) == scene)
			{
				LeaveCriticalSection(&lock);
				return;
			}
		}		
		scenes.push_back(scene);
		LeaveCriticalSection(&lock);
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

void VisualSystem::removeScene( VisualScene* scene )
{
	if(isVisualInited)
	{
		EnterCriticalSection(&lock);
		for(u32 i=0 ; i<scenes.size() ; i++)
		{
			if(scenes.at(i) == scene)
			{
				scene->cleanUp();
				scenes.erase(scenes.begin()+i);
				return;
			}
		}
		LeaveCriticalSection(&lock);
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

DWORD WINAPI VisualSystem::visualThreadProc( LPVOID param )
{
	VisualSystem* This = (VisualSystem*)param;

	InitializeCriticalSection(&This->lock);
	EnterCriticalSection(&This->lock);
	try
	{
		if(This->createVisualRoot())
		{
			if(This->createRenderSystem())
			{
				This->createInternalPlugins();				
				This->createSceneMgr();
				This->createRenderWindow();
				This->createRenderCamera();
				This->createRenderViewport();

				This->isVisualInited = true;				
			}
		}
	}
	catch (...)
	{
		LeaveCriticalSection(&This->lock);
		SetEvent(This->visualInitSignal);
	}
	LeaveCriticalSection(&This->lock);
	SetEvent(This->visualInitSignal);

	This->currentFrame	   = 0;
	This->maxFPS = 0;
	f64 totalslice = 0;
	u64 usedtick       = 0;	
	u32 framePerSecond = 60;

	LARGE_INTEGER starttick;
	LARGE_INTEGER tick;
	LARGE_INTEGER tickPerSecond;

	QueryPerformanceFrequency(&tickPerSecond);
	QueryPerformanceCounter(&tick);
	
	while(This->isVisualRunning && !This->primaryRenderWindow->isClosed() && This->isVisualInited)
	{
		u32 result = WaitForSingleObject(This->visualThreadSignal,INFINITE);
		if(result == WAIT_OBJECT_0 && This->isVisualRunning)
		{
			QueryPerformanceCounter(&starttick);

			Ogre::WindowEventUtilities::messagePump();
			EnterCriticalSection(&This->lock);
			try
			{
				for(u32 i=0 ; i<This->scenes.size() ; i++)
				{
					This->scenes.at(i)->update();
				}
				This->visualRoot->renderOneFrame();				
			}
			catch (...)
			{
				LeaveCriticalSection(&This->lock);
			}
			LeaveCriticalSection(&This->lock);

			This->currentFrame++;
			u64 lasttick = tick.QuadPart;
			u32 frameleft = framePerSecond - This->currentFrame;
			QueryPerformanceCounter(&tick);

			if( ((usedtick+(tick.QuadPart - lasttick)) < (u64)tickPerSecond.QuadPart) && frameleft)
			{			
				u64 deltatick = tick.QuadPart - starttick.QuadPart;
				usedtick     += tick.QuadPart - lasttick;
				u64 tickleft  = tickPerSecond.QuadPart - usedtick;
				u64 sleeptick = tickleft/frameleft;
				u32 sleepMS   = (u32)(1000*sleeptick/tickPerSecond.QuadPart);	
				totalslice   += (f32)(f64(1000*deltatick)/f64(tickPerSecond.QuadPart));

				Sleep(sleepMS);
			}
			else
			{
				usedtick = 0;
				This->currentFrame = 0;
				frameleft = framePerSecond;
				This->maxFPS = 1000.0f/f32(totalslice/f64(framePerSecond));
				totalslice = 0;
			}
		}
	}

	EnterCriticalSection(&This->lock);
	This->isVisualRunning = false;
	This->cleanUp();
	LeaveCriticalSection(&This->lock);
	DeleteCriticalSection(&This->lock);

	return 0;
}

//————————————————————————————————————————————————————————————————————————————————————————

void VisualSystem::waitUntilEnd()
{
	if(WaitForSingleObject(visualThread,INFINITE) == WAIT_OBJECT_0)
	{
		return;
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

void VisualSystem::lockThread()
{
	EnterCriticalSection(&lock);
}

//————————————————————————————————————————————————————————————————————————————————————————

void VisualSystem::unlockThread()
{
	LeaveCriticalSection(&lock);
}
//————————————————————————————————————————————————————————————————————————————————————————
