#ifndef VISUALSYSTEM_H
#define VISUALSYSTEM_H

#include "transporter.h"

class VisualSystem
{
protected : Ogre::RenderWindow* renderWindow;
			Ogre::RenderSystem* renderSystem;
			Ogre::Camera* renderCamera;
			Ogre::Viewport* renderViewport;
			Ogre::SceneManager* sceneMgr;
			Ogre::Root* visualRoot;
			Ogre::GLPlugin* glPlugin;
			Ogre::OctreePlugin* octreePlugin;
			Ogre::CgPlugin* cgPlugin;
			VisualScene* scene;
			Game* game;
			HWND renderWindowHandle;
			bit isVisualRunning;
			bit isVisualInited;	
			void cleanUp();
			static DWORD WINAPI visualThreadProc(LPVOID param);

public    : VisualSystem();
			~VisualSystem();
					
			bit init(Game* game);
			void run(VisualScene* scene);
			void stop();		
			bit isRunnning();
			HWND getWindowHandle();

			Ogre::RenderWindow* getRenderWindow();
			Ogre::RenderSystem* getRenderSystem();
			Ogre::Camera* getCamera();
			Ogre::SceneManager* getSceneMgr();
};
#endif