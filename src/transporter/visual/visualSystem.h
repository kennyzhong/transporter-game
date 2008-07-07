#ifndef VISUALSYSTEM_H
#define VISUALSYSTEM_H

#include "transporter.h"

class VisualSystem
{
protected : Ogre::RenderSystem* renderSystem;
			Ogre::RenderWindow* primaryRenderWindow;
			Ogre::SceneManager* sceneMgr;
			Ogre::Root* visualRoot;
			VisualScene* scene;
			VisualLogListener logListener;
			Game* game;
			CRITICAL_SECTION lock;
			bit isVisualRunning;
			bit isVisualInited;	
			bit isVisualBooted;
			u32 currentFrame;
			HANDLE visualThread;
			HANDLE visualThreadSignal;
			HANDLE visualInitSignal;
			f32 maxFPS;

			std::vector<Ogre::Plugin*> plugins;
			std::map<str,Ogre::RenderWindow*> renderWindows;			
			std::vector<Ogre::Camera*> renderCameras;
			std::vector<Ogre::Viewport*> renderViewports;	
			std::vector<VisualScene*> scenes;

			void cleanUp();
			bit createVisualRoot();
			bit createRenderSystem();
			bit createInternalPlugins();			
			bit createSceneMgr();
			bit createRenderCamera();
			bit createRenderWindow();
			bit createRenderViewport();		
			static DWORD WINAPI visualThreadProc(LPVOID param);

public    : VisualSystem();
			~VisualSystem();
					
			bit init(Game* game);
			void waitUntilEnd();
			bit boot();
			void run();
			void stop();		
			bit isRunnning();
			u32 getCurrentFrameNum();
			HWND getWindowHandle(Ogre::RenderWindow* window);
			void addScene(VisualScene* scene);
			void removeScene(VisualScene* scene);
			void lockThread();
			void unlockThread();
			bit loadResources(str resourceGroupName);
			f32 getMaxFPS(){return maxFPS;}
		
			Ogre::RenderWindow* getRenderWindow(str name);	
			Ogre::RenderWindow* getPrimaryRenderWindow();
			Ogre::Camera* getCamera(u32 index=0);
			Ogre::Camera* getCamera(str name);
			Ogre::RenderSystem* getRenderSystem();
			Ogre::SceneManager* getSceneMgr();
};
#endif